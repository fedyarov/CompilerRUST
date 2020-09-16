#include "Generator.h"

Generator::Generator(const std::string& pathToFile) : m_parser(pathToFile)
{
	bytes_on_stack = 8;
	label_count = 0;
	std::string res_path(pathToFile);
	res_path.pop_back(); // delete 's'
	res_path.pop_back(); // delete 'r'
	out.open(res_path + "asm");
}

void Generator::Generate()
{
	m_parser.parse();
	m_ast_root = m_parser.getAst();
	var_table = m_parser.getVariable_table();

	ASMLocalVars();
	ASMPrintDeclaration();
	ASMCodeForBlocks(m_ast_root);

	std::cout << "INFO: Successfully generated!" << std::endl;

	WriteInOutputFile(asmHeader);

	WriteInOutputFile(startData);
	WriteInOutputFile(ASMDataSegment);
	WriteInOutputFile(endData);
	
	WriteInOutputFile(textStart);
	WriteInOutputFile(ASMTextSegment);
	WriteInOutputFile(labelStart);
	WriteInOutputFile(procProlog + std::to_string(var_table->size() * 4 + 4) + ", 0");
	WriteInOutputFile(ASMMainSegment);
	WriteInOutputFile(procEpilogue);
	WriteInOutputFile(functionReturn);
	WriteInOutputFile(textEnd);
	WriteInOutputFile(labelEnd);
}

void Generator::ASMCodeForBlocks(Node* node)
{
	if (node == nullptr)
		return;

	if (node->type == node_type::SET){
		ASMSet(node);
		return;
	}
	if (node->type == node_type::PRINTLN) {
		ASMPrintCall(node);
		return;
	}
	if (node->type == node_type::IF) {
		ASMIf(node);
		return;
	}
	if (node->type == node_type::LESS ||
		node->type == node_type::MORE ||
		node->type == node_type::EQUALITY) {
		ASMCondition(node);
		return;
	}
	if (node->type == node_type::FOR) {
		ASMFor(node);
		return;
	}
	

	ASMCodeForBlocks(node->operand1);
	ASMCodeForBlocks(node->operand2);
	ASMCodeForBlocks(node->operand3);
	ASMCodeForBlocks(node->operand4);
}

void Generator::ASMSet(Node* node)
{
	Node* op1 = node->operand1;
	Node* op2 = node->operand2;

	if (op1->type == node_type::VARIABLE) {
		std::string var_name = op1->value;

		ASMAdditive_expression(op2);
		Pop(eax);
		Move(GetASMLocalVar(var_name), eax);
	}
	else {
		throw std::logic_error("Generate error! Variable exprected before '=' !");
	}
}

void Generator::ASMAdditive_expression(Node* node)
{
	if (node == nullptr)
		return;

	if (node->type == node_type::ADD)
	{
		ASMAdditive_expression(node->operand1);
		ASMAdditive_expression(node->operand2);

		Pop(eax);
		Pop(ebx);
		Add(eax, ebx);
		Push(eax);
	}
	else if (node->type == node_type::SUB)
	{
		ASMAdditive_expression(node->operand1);
		ASMAdditive_expression(node->operand2);

		Pop(ebx);
		Pop(eax);
		Sub(eax, ebx);
		Push(eax);
	}
	else if (node->type == node_type::MUL)
	{
		ASMAdditive_expression(node->operand1);
		ASMAdditive_expression(node->operand2);

		Pop(eax);
		Pop(ebx);
		Imul(eax, ebx);
		Push(eax);
	}
	else if (node->type == node_type::DIV)
	{
		ASMAdditive_expression(node->operand1);
		ASMAdditive_expression(node->operand2);

		Move(ecx, "0");
		Pop(ebx);
		Raw(tab + "cdq\n");
		Pop(eax);
		Idiv(ebx);
		Push(eax);
	}
	else if (node->type == node_type::NUMBER)
	{
		std::string num_value = node->value;
		Push(num_value);
	}
	else if (node->type == node_type::VARIABLE)
	{
		std::string var_name = node->value;
		Push(GetASMLocalVar(var_name));
	}
}

void Generator::ASMPrintCall(Node* node)
{
	if (node->operand1 != nullptr) {
		ASMAdditive_expression(node->operand1);
		Raw(tab + "call print\n");
	}
}

void Generator::ASMIf(Node* node)
{
	Node* condition = node->operand1;
	Node* statement = node->operand2;
	Node* else_block = node->operand3;

	++label_count;
	std::string else_label = "ELSE_START" + std::to_string(label_count);
	std::string end_label = "IF_END" + std::to_string(label_count);

	ASMCodeForBlocks(condition);
	Pop(eax);
	Compare(eax, null);

	if (else_block == nullptr)
	{
		JumpEqual(end_label);
		ASMCodeForBlocks(statement);
		Label(end_label);
	}
	else
	{
		JumpEqual(else_label);
		ASMCodeForBlocks(statement);
		Jump(end_label);

		Label(else_label);
		ASMCodeForBlocks(else_block);
		Label(end_label);
	}
}

void Generator::ASMCondition(Node* node)
{
	Node* op1 = node->operand1;
	Node* op2 = node->operand2;

	ASMAdditive_expression(op1);
	Pop(ecx);
	ASMAdditive_expression(op2);
	Pop(edx);
	Compare(ecx, edx);

	++label_count;
	std::string label_if_not_equal = "COMPARE_FALSE" + std::to_string(label_count);
	std::string label_comp_end = "COMPARE_END" + std::to_string(label_count);

	if (node->type == node_type::LESS)
	{
		JumpGreaterEqual(label_if_not_equal);
	}
	else if (node->type == node_type::MORE)
	{
		JumpLessEqual(label_if_not_equal);
	}
	else if (node->type == node_type::EQUALITY)
	{
		JumpNotEqual(label_if_not_equal);
	}

	Push(one);
	Jump(label_comp_end);
	Label(label_if_not_equal);
	Push(null);
	Label(label_comp_end);

	return;
}

void Generator::ASMFor(Node* node)
{
	++label_count;
	std::string start_label = "START_FOR" + std::to_string(label_count);
	std::string end_label = "END_FOR" + std::to_string(label_count);
	++label_count;
	std::string label_if_not_equal = "COMPARE_FALSE" + std::to_string(label_count);
	std::string label_comp_end = "COMPARE_END" + std::to_string(label_count);

	label_stack.push(end_label);

	Node* var = node->operand1;
	Node* init_val = node->operand2; //range starting additive_expression
	Node* end_val = node->operand3;	 //ranfe ending additive_expression
	Node* statement = node->operand4;

	ASMAdditive_expression(init_val);
	Pop(eax);
	Move(GetASMLocalVar(var->value), eax);

	Label(start_label);

	Push(GetASMLocalVar(var->value));
	Pop(ecx);
	ASMAdditive_expression(end_val);
	Pop(edx);
	Compare(ecx, edx);
	JumpGreaterEqual(label_if_not_equal);
	Push(one);
	Jump(label_comp_end);
	Label(label_if_not_equal);
	Push(null);
	Label(label_comp_end);

	Pop(eax);
	Compare(eax, null);
	JumpEqual(end_label);
	ASMCodeForBlocks(statement);
	Push(GetASMLocalVar(var->value));
	Pop(eax);
	Add(eax, "1");
	Move(GetASMLocalVar(var->value), eax);
	Jump(start_label);
	Label(end_label);

	label_stack.pop();
}

void Generator::ASMLocalVars()
{
	for (auto& it : var_table->vars) {
		ASMStackVar(it->get_name());
	}
	bytes_on_stack = 4;
}

void Generator::ASMStackVar(const std::string& value)
{
	std::string var_name = value;
	size_t var_size = 4;
	ASMTextSegment.append(var_name + " = " + "-" + std::to_string(bytes_on_stack) + "\n");
	bytes_on_stack += var_size;
}

void Generator::ASMPrintDeclaration()
{
	SetASMSegment(AssemblerPart::DATA_SEGMENT);
	Raw(tab + "print_format db \"%d \", 0\n");

	SetASMSegment(AssemblerPart::TEXT_SEGMENT);
	Raw("\nprint PROC\n");
	Raw(tab + "enter 0, 0\n");

	Move(eax, "[ebp + 8]");
	Raw(tab + "invoke crt_printf, offset print_format, eax\n");

	Raw(tab + "leave\n");
	Raw(tab + "ret 4\n");
	Raw("print ENDP\n");

	SetASMSegment(AssemblerPart::MAIN_SEGMENT);
}

void Generator::SetASMSegment(AssemblerPart place)
{
	switch (place){
		case AssemblerPart::DATA_SEGMENT:{
			ASMCurrentSegment = &ASMDataSegment;
			break;
		}
		case AssemblerPart::TEXT_SEGMENT:{
			ASMCurrentSegment = &ASMTextSegment;
			break;
		}
		case AssemblerPart::MAIN_SEGMENT:{
			ASMCurrentSegment = &ASMMainSegment;
			break;
		}
	}
}

std::string Generator::GetASMLocalVar(const std::string& value)
{
	return value + "[ebp]";
}

void Generator::WriteInOutputFile(const std::string& text)
{
	out << text << "\n";
}

void Generator::Push(const std::string& value)
{
	ASMCurrentSegment->append(tab + "push " + value + "\n");
}

void Generator::Pop(const std::string& value)
{
	ASMCurrentSegment->append(tab + "pop " + value + "\n");
}

void Generator::Add(const std::string& value1, const std::string& value2)
{
	ASMCurrentSegment->append(tab + "add " + value1 + ", " + value2 + "\n");
}

void Generator::Sub(const std::string& value1, const std::string& value2)
{
	ASMCurrentSegment->append(tab + "sub " + value1 + ", " + value2 + "\n");
}

void Generator::Imul(const std::string& value1, const std::string& value2)
{
	ASMCurrentSegment->append(tab + "imul " + value1 + ", " + value2 + "\n");
}

void Generator::Idiv(const std::string& value1)
{
	ASMCurrentSegment->append(tab + "idiv " + value1 + "\n");
}

void Generator::Move(const std::string& value1, const std::string& value2)
{
	ASMCurrentSegment->append(tab + "mov " + value1 + ", " + value2 + "\n");
}

void Generator::Raw(const std::string& value)
{
	ASMCurrentSegment->append(value);
}

void Generator::Compare(const std::string& value1, const std::string& value2)
{
	ASMCurrentSegment->append(tab + "cmp " + value1 + ", " + value2 + "\n");
}

void Generator::Jump(const std::string& value)
{
	ASMCurrentSegment->append(tab + "jmp " + value + "\n");
}

void Generator::JumpEqual(const std::string& value)
{
	ASMCurrentSegment->append(tab + "je " + value + "\n");
}

void Generator::JumpNotEqual(const std::string& value)
{
	ASMCurrentSegment->append(tab + "jne " + value + "\n");
}

void Generator::JumpLess(const std::string& value)
{
	ASMCurrentSegment->append(tab + "jl " + value + "\n");
}

void Generator::JumpLessEqual(const std::string& value)
{
	ASMCurrentSegment->append(tab + "jle " + value + "\n");
}

void Generator::JumpGreater(const std::string& value)
{
	ASMCurrentSegment->append(tab + "jg " + value + "\n");
}

void Generator::JumpGreaterEqual(const std::string& value)
{
	ASMCurrentSegment->append(tab + "jge " + value + "\n");
}

void Generator::Label(const std::string& value)
{
	ASMCurrentSegment->append(value + ":\n");
}

#pragma once
#include <fstream>
#include "Parser.h"
#include <stack>
#include <string>

const std::string asmHeader = ".586\n"
".model flat, stdcall\n\n"
"include <C:\\masm32\\include\\msvcrt.inc>\n"
"include <C:\\masm32\\include\\kernel32.inc>\n"
"includelib <C:\\masm32\\lib\\msvcrt.lib>\n"
"includelib <C:\\masm32\\lib\\kernel32.lib>\n";

const std::string startData = "data segment\n";
const std::string endData = "data ends\n";
const std::string textStart = "text segment\n";
const std::string textEnd = "text ends\n";
const std::string labelStart = "__start:\n";
const std::string labelEnd = "end __start\n";
const std::string procProlog = "   enter ";
const std::string procEpilogue = "   leave\n";
const std::string functionReturn = "   ret\n";
const std::string programExit = "   GenPush 0\n"
"   call ExitProcess\n";
const std::string tab = "   ";

const std::string eax("eax");
const std::string ebx("ebx");
const std::string ecx("ecx");
const std::string edx("edx");
const std::string null("0");


enum class AssemblerPart {
	DATA_SEGMENT,
	TEXT_SEGMENT,
	MAIN_SEGMENT,
};

class Generator
{
	Parser m_parser;
	Node* m_ast_root;
	Variable_table* var_table;

	std::ofstream out;

	std::string ASMDataSegment;
	std::string ASMTextSegment;
	std::string ASMMainSegment;
	std::string* ASMCurrentSegment;

	int bytes_on_stack;
	int label_count;

	std::stack<std::string> label_stack;
public:
	Generator(const std::string& pathToFile);
	
	void Generate();
private:
	void ASMCodeForBlocks(Node* node);
	void ASMSet(Node* node);
	void ASMAdditive_expression(Node* node);
	void ASMPrintCall(Node* node);

	void ASMLocalVars();
	void ASMStackVar(const std::string& value);
	void ASMPrintDeclaration();
	void SetASMSegment(AssemblerPart place);
	std::string GetASMLocalVar(const std::string& value);

	void WriteInOutputFile(const std::string& text);

	void Push(const std::string& value);
	void Pop(const std::string& value);
	void Add(const std::string& value1, const std::string& value2);
	void Sub(const std::string& value1, const std::string& value2);
	void Imul(const std::string& value1, const std::string& value2);
	void Idiv(const std::string& value);
	void Move(const std::string& value1, const std::string& value2);
	void Raw(const std::string& value);
	void Compare(const std::string& value1, const std::string& value2);
	void Jump(const std::string& value);
	void JumpEqual(const std::string& value);
	void JumpNotEqual(const std::string& value);
	void JumpLess(const std::string& value);
	void JumpLessEqual(const std::string& value);
	void JumpGreater(const std::string& value);
	void JumpGreaterEqual(const std::string& value);
	void Label(const std::string& value);
};


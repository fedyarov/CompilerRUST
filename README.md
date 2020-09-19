# CompilerRUST
В данном проекте представлен компилятор для подмножества языка Rust, написанный на C++.
В нем реализованы основные стадии работы современных компиляторов. 

На вход подается файл с исходным кодом. **Лексический анализатор** выделяет из лексем все *токены*. 
Они поступают в **синтаксический анализатор**, которой строит *AST*. *Абстрактное синтаксическое дерево* строится по грамматике, которая описана при помощи формальной 
системы определения синтаксиса *EBNF*. В финальной стадии к работе приступает **генератор кода**, который генерирует *ассемблерный код* по полученному ранее *AST*.

## Лексический анализатор
Каждый токен является объектом класса [Token](https://github.com/fedyarov/CompilerRUST/blob/master/Token.h "Token.h"). В этом файле также содержится 
строго-типизированное перечисление `enum class token_type`, в котором находятся все известные компилятору токены.

За лексический анализ отвечает класс [Lexer](https://github.com/fedyarov/CompilerRUST/blob/master/Lexer.h "Lexer.h"). Он хранит в себе вектор 
токенов `vector<Token*> tokens`, указатель на текущий токен `size_t current_token_index` и методы для анализа и дальнейшего синтаксического анализа. 

## Синтаксический анализатор
Класс [Parser](https://github.com/fedyarov/CompilerRUST/blob/master/Parser.h "Parser.h") содержит в себе три указателя. С лексером все ясно. Интерес представляют
остальные члены класса. 

    class Parser
    {
      Lexer* lex;
      Ast* ast;
      Variable_table* var_table;
      ...
    }

Первый из них, это объект класса синтаксического дерева [Ast](https://github.com/fedyarov/CompilerRUST/blob/master/Ast.h "Ast.h"), внутри которого содержится указатель на объект
класса [Node](https://github.com/fedyarov/CompilerRUST/blob/master/Node.h "Node.h"). Типы узлов представлены в перечислении `enum class node_type` в файле 
[Node.h](https://github.com/fedyarov/CompilerRUST/blob/master/Node.h "Node.h"). Тип узла задает действие, которое необходимо сделать с потомками:
1) Объявления переменных `DCLRT`;
2) Присваивания `SET`;
3) Выражения `EXPR`, в том числе логические `MORE`, `LESS`, `EQUALITY`;
4) Условные переходы `IF`, `ELSE`;
5) Цикл `FOR`;
6) Математические операции `ADD`, `SUB`, `MUL`, `DIV`;
7) Переменные `VARIABLE` и константные целочисленные значения `NUMBER`;
8) Вывод значения переменной `PRINTLN`;

Составление *AST* - один из главных процессов для последующей генерации кода. Дерево строится *методом рекурсивного спуска*. Грамматика языка описана с
помощью *расширенной формы Бэкуса-Наура* в файле [EBNF.txt](https://github.com/fedyarov/CompilerRUST/blob/master/EBNF/EBNF.txt "EBNF.txt"). Ниже показан пример описания 
*нетерминала* условия `if-else`.

    ...
    <compound_statement> ::= "{", <statement>, "}"
    <selection_statement> ::= "if", <expression>, <compound_statement>,
						                ["else", <compound_statement>]
    ...

В итоге для фрагмента кода: 

	if var2 < var1*2 {
		println!("{}",var2);
	}

Получим следующее *AST*:

	+-SEQ
          +-IF
            +-LESS
              +-VARIABLE (var2)
              +-MUL
                +-VARIABLE (var1)
                +-NUMBER (2)
            +-SEQ
              +-PRINTLN
                +-VARIABLE (var2)

`Примечание:` узел `SEQuence` необходим для хранения в нем *последовательной* инструкции. 

## Генератор кода
Объект класса [Generator](https://github.com/fedyarov/CompilerRUST/blob/master/Generator.h "Generator.h") создается в функции `int main(int argc, char* argv[])` и там же 
вызывается его метод `Generate`.

      try {
		  generator.Generate();
	  }
	  catch (const logic_error& error) {
		  cout << error.what() << endl;
	  }

При помощи рекурсии генератор кода обходит созданное парсером *AST* и добавляет необходимые строчки ассемблерного кода в файл `*.asm`.

## Примеры работы программы
Все примеры с исходным кодом, лог файлом, и сгенерированным ассемблерным кодом можно просмотреть в папке [Tests](https://github.com/fedyarov/CompilerRUST/tree/master/Tests).

В файлах `*.rs` находится исходный код на языке Rust. Например, [Condition.rs](https://github.com/fedyarov/CompilerRUST/blob/master/Tests/condition_test/Condition.rs).

В файле `log.txt` можно отследить выходные данные всех этапов работы компилятора. Например, 
[log.txt](https://github.com/fedyarov/CompilerRUST/blob/master/Tests/condition_test/log.txt) для программы строчкой выше.

И наконец, в файле `*.asm` находится сгенерированный ассемблерный код. [Condition.asm](https://github.com/fedyarov/CompilerRUST/blob/master/Tests/condition_test/Condition.asm)
для файла, приведенного в пример выше.

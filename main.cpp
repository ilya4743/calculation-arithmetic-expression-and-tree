#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdlib>
#include<conio.h>

using namespace std;

struct Node 
{
	char data;
	Node *left, *right;
};

typedef Node *PNode;

int Priority(char c)
{
	switch (c)
	{
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
	return 100;
}

PNode MakeTree(char Expr[], int first, int last)
{
	int MinPrt, i, k, prt;
	int nest = 0; // счетчик открытых скобок
	PNode Tree = new Node;
	if (first == last) { // конечная вершина: число или
		Tree->data = Expr[first]; // переменная
		Tree->left = NULL;
		Tree->right = NULL;
		return Tree;
	}
	MinPrt = 100;
	for (i = first; i <= last; i++) {
		if (Expr[i] == '(') // открывающая скобка
		{
			nest++; continue;
		}
		if (Expr[i] == ')') // закрывающая скобка
		{
			nest--; continue;
		}
		if (nest > 0) continue; // пропускаем все, что в скобках
		prt = Priority(Expr[i]);
		if (prt <= MinPrt) {
			MinPrt = prt;
			k = i;
		}
	}
	if (MinPrt == 100 && // все выражение взято в скобки
		Expr[first] == '(' && Expr[last] == ')') {
		delete Tree;
		return MakeTree(Expr, first + 1, last - 1);
	}
	Tree->data = Expr[k]; // внутренняя вершина (операция)
	Tree->left = MakeTree(Expr, first, k - 1); // рекурсивно строим
	Tree->right = MakeTree(Expr, k + 1, last); // поддеревья
	return Tree;
}

int CalcTree(PNode Tree)
{
	int num1, num2;
	if (!Tree->left) // если нет потомков,
		return Tree->data - '0'; // вернули число
	num1 = CalcTree(Tree->left); // вычисляем поддеревья
	num2 = CalcTree(Tree->right);
	switch (Tree->data) { // выполняем операцию
	case '+': return num1 + num2;
	case '-': return num1 - num2;
	case '*': return num1*num2;
	case '/': return num1 / num2;
	}
	return 32767; // неизвестная операция, ошибка!
}

void DeleteNode(PNode Tree)
{
	if (Tree == NULL) return;
	DeleteNode(Tree->left);
	DeleteNode(Tree->right);
	delete Tree;
}


void PrintLKP(PNode Tree)
{
	if (!Tree) return; // пустое дерево – окончание рекурсии
	PrintLKP(Tree->left); // обход левого поддерева
	printf("%c ", Tree->data); // вывод информации о корне
	PrintLKP(Tree->right); // обход правого поддерева
}

void PrintLPK(PNode Tree)
{
	if (Tree) {
		; // пустое дерево – окончание рекурсии
		PrintLPK(Tree->left); // обход левого поддерева
		PrintLPK(Tree->right); // обход правого поддерева
		printf("%c ", Tree->data);
	} // вывод информации о корне
}

int main()
{
	setlocale(LC_ALL, "rus");
	char s[80];
	PNode Tree;
	cout << "Введите выражение: ";
	cin.getline(s, 80);
	Tree = MakeTree(s, 0, strlen(s) - 1);
	cout << "ЛКП: ";
	PrintLKP(Tree);
	cout << endl;
	cout << "ЛПК: ";
	PrintLPK(Tree);
	cout << endl;
	cout << "Значение арифметического выражения: " << CalcTree(Tree);
	DeleteNode(Tree);
	_getch();
	return 0;
}

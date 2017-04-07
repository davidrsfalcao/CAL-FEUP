#include "uteis.h"
#include <stdlib.h>

//#pragma warning(disable: 4996)

using namespace std;

int horas_do_sistema(){
	time_t rawtime;
	struct tm *ptm;

	time ( &rawtime );

	ptm = gmtime ( &rawtime );


	return ptm->tm_hour+0;


}

int minutos_do_sistema(){
	time_t rawtime;
	struct tm *ptm;

	time ( &rawtime );

	ptm = gmtime ( &rawtime );


	 return ptm->tm_min;

}

int dia_do_sistema(){
	int dia;

	time_t rawtime;
	struct tm *timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	dia = timeinfo->tm_mday;

	return dia;
}

int mes_do_sistema(){
	int mes;

	time_t rawtime;
	struct tm *timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	mes = timeinfo->tm_mon + 1;

	return mes;
}

string mostrar_mes(unsigned int mes){

	switch(mes)
	{
	case 1:
		return "janeiro";

	case 2:
			return "fevereiro";

	case 3:
			return "marco";

	case 4:
			return "abril";

	case 5:
			return "maio";

	case 6:
			return "junho";

	case 7:
			return "julho";

	case 8:
			return "agosto";

	case 9:
			return "setembro";

	case 10:
			return "outubro";

	case 11:
			return "novembro";

	case 12:
			return "dezembro";

	default:
			return "#erro";

	}

}

int ano_do_sistema(){
	int ano;

	time_t rawtime;
	struct tm *timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	ano = timeinfo->tm_year + 1900;

	return ano;
}

void limparEcra(){

	system("cls");

}

unsigned short int leUnsignedShortInt(unsigned short int min, unsigned short int  max){

	unsigned short int opcao;
	char temp;

	cin >> temp;
	opcao = temp;

	if (opcao == 114)
		return 0;

	opcao -= 48;

	while (opcao > max || opcao < min)
	{
		cerr << " Opcao invalida. Tente de novo.\n";
		cin.clear();
		cin.ignore(256, '\n');
		cout << "\n Opcao: ";
		cin >> temp;
		opcao = temp;

		if (opcao == 114)
			return 0;

		opcao -= 48;
	}

	return opcao;
}

string delete_space(string str){
	string new_str = "", new_str1 = "";
	char espaco = ' ' ;


	for (size_t i = 0; i<str.length(); i++)
	{
		if (str[i] == espaco)
			continue;
		else for (; i < str.length(); i++)
		{
			new_str = new_str + str[i];
		}
	}


	for (size_t i = new_str.length() - 1; i >= 0; i--)
	{
		if (new_str[i] == espaco)
			continue;
		else for (; i >= 0; i--)
		{
			new_str1 = new_str[i] + new_str1;
		}
	}

	return new_str1;
}

string calculo_dia_da_semana(int dia,int mes,int ano){
	switch (mes) {
	case 1:
		break;
	case 2:
		dia += 31;
		break;
	case 3:
		dia += 59;
		break;
	case 4:
		dia += 90;
		break;
	case 5:
		dia += 120;
		break;
	case 6:
		dia += 151;
		break;
	case 7:
		dia += 181;
		break;
	case 8:
		dia += 212;
		break;
	case 9:
		dia += 243;
		break;
	case 10:
		dia += 273;
		break;
	case 11:
		dia += 304;
		break;
	case 12:
		dia += 334;
		break;
	}
	if (((ano % 4) == 0) && (((ano % 100) != 0) || ((ano % 400) == 0)) && (mes > 2))
		dia += 1;

	dia += -1 + (ano - 1) * 365 + (ano - 1) / 4 - (ano - 1) / 100 + (ano - 1) / 400;

	switch (dia % 7) {
	case 0:
		return "segunda";
		break;

	case 1:
		return "terca";
		break;

	case 2:
		return "quarta";
		break;

	case 3:
		return "quinta";
		break;

	case 4:
		return "sexta";
		break;

	case 5:
		return "sabado";
		break;

	case 6:
		return "domingo";
		break;
	}

	return "#erro";

}

void cabecalho(){
	int a = 186;
	char char1 = a;  // obter -> â•‘

	int b = 201;
	char char2 = b; // obter -> â•”

	int c = 205;
	char char3 = c; // obter -> â•�

	int d = 187;
	char char4 = d; // obter -> â•—

	int e = 200;
	char char5 = e; // obter -> â•š

	int f = 188;
	char char6 = f; // obter -> â•�

	textcolor(yellow);
	cout << "\t      " << char2 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char4 << endl;
	cout << "\t      " << char1;
	textcolor(white);
	cout << "   Hora: ";
	if (horas_do_sistema() < 10)
		cout << "0" << horas_do_sistema() << ":";
	else
		cout << horas_do_sistema() << ":";

	if (minutos_do_sistema() < 10)
		cout << "0" << minutos_do_sistema();
	else
		cout << minutos_do_sistema();

	int dia, mes, ano;
	dia = dia_do_sistema();
	mes = mes_do_sistema();
	ano = ano_do_sistema();

	cout << "\t\t" << calculo_dia_da_semana(dia, mes, ano) << ", " << dia
		<< " de " << mostrar_mes(mes) << " de " << ano;

	textcolor(yellow);
	gotoxy(75, 1);
	cout << char1 << endl;
	cout << "\t      " << char5 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char6 << endl;
	textcolor(white);
}

int encontra_string_vetor(string palavra, vector<string> v1){
	bool encontrou = false;
	int indice;

	for (size_t i = 0; i < v1.size(); i++)
	{
		if (v1[i] == palavra)
		{
			encontrou = true;
			indice = i;
			break;

		}

	}

	if (encontrou)
		return indice;
	else return -1;


}

bool dia_existe(int dia, int mes, int ano){
	if ((dia > 31) || (mes > 12))
		return false;
	else
	switch (mes)
	{
	case 1: //janeiro
		if(dia > 31)
			return false;
		else return true;

	case 2: //fevereiro
		if (ano % 4 == 0 && (ano % 400 == 0 || ano % 100 != 0))
			if (dia > 29)
				return false;
			else return true;
		else if (dia > 28)
			return false;
		else return true;
		break;

	case 3: //marco
		if(dia > 31)
			return false;
		else return false;
		break;

	case 4:  //abril
		if(dia > 30)
			return false;
		else return true;
		break;

	case 5:  // maio
		if(dia > 31)
			return false;
		else return true;
		break;

	case 6: // junho
		if(dia > 30)
			return false;
		else return true;
		break;

	case 7: // julho
		if(dia > 31)
			return false;
		else return true;
		break;

	case 8: // agosto
		if(dia > 31)
			return false;
		else return true;
		break;

	case 9:  // setembro
		if(dia > 30)
			return false;
		else return true;
		break;

	case 10: // outubro
		if(dia > 31)
			return false;
		else return true;
		break;

	case 11: // novembro
		if(dia > 30)
			return false;
		else return true;
		break;

	case 12: // dezembro
		if(dia > 31)
			return false;
		else return true;
		break;

	}

	return true;



}

int opcao_valida(int &opcao, int min, int max){
	int tecla;
	int make=0, breakc=0;
	make = _getch();

	if (make == 224)
		breakc = _getch();
	else return make;

	tecla = make * 100 + breakc;

	if (tecla == DOWN_KEY)
		opcao--;

	if (tecla == UP_KEY)
		opcao++;

	if (opcao > max)
		opcao = min;

	if (opcao < min)
		opcao = max;

	return tecla;

}

int opcao_valida_listas(int &opcao, int min, int max){
	int tecla;
	int make = 0, breakc = 0;
	make = _getch();

	if (make == 224)
		breakc = _getch();
	else return make;

	tecla = make * 100 + breakc;

	if (tecla == LEFT_KEY)
		opcao--;

	if (tecla == RIGHT_KEY)
		opcao++;

	if (opcao > max)
		opcao = min;

	if (opcao < min)
		opcao = max;

	return tecla;

}

int tecla_pressionada(){
	int tecla;
	int make = 0, breakc = 0;
	make = _getch();

	if (make == 224)
		breakc = _getch();
	else return make;

	tecla = make * 100 + breakc;

	return tecla;

}

void textcolor(DOS_COLORS iColor){
	HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	GetConsoleScreenBufferInfo(hl, &bufferInfo);
	bufferInfo.wAttributes &= 0x00F0;
	SetConsoleTextAttribute(hl, bufferInfo.wAttributes |= iColor);
}

void titulo(){
	limparEcra();

	int a = 186;
	char char1 = a;  // obter -> â•‘

	int b = 201;
	char char2 = b; // obter -> â•”

	int c = 205;
	char char3 = c; // obter -> â•�

	int d = 187;
	char char4 = d; // obter -> â•—

	int e = 200;
	char char5 = e; // obter -> â•š

	int f = 188;
	char char6 = f; // obter -> â•�

	int g = 219;
	char i = g; // obter -> â–ˆ

	textcolor(yellow);
	cout << "\t      " << char2 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char4 << endl;

	cout << "\t      "<<char1 << "   "  <<i<<i<<i<<i<<i<<  "   " <<i<<i<<"  "<<i<<i<<i<<i<<i<<i<<  "                                       " << char1 << endl;
	cout << "\t      "<<char1 << "  "<<i<<i<< "   " <<i<<i<<"  "<<i<<i<<"  "<<i<<i<< "   " <<i<<i<<"                                      " << char1 << endl;
	cout << "\t      "<<char1 << "  "<<i<<i<< "   " <<i<<i<<"  "<<i<<i<<"  "<<i<<i<< "   " <<i<<i<<"                                      " << char1 << endl;
	cout << "\t      "<<char1 << "  "<<i<<i<<i<<i<<i<<i<<i<<"  "<<i<<i<<"  "<<i<<i<<i<<i<<i<<i<<i<<i<<"                                     " << char1 << endl;
	cout << "\t      "<<char1 << "  "<<i<<i<< "   " <<i<<i<<"  "<<i<<i<<"  "<<i<<i<< "     " <<i<<i<<"                                    " << char1 << endl;
	cout << "\t      "<<char1 << "  "<<i<<i<< "   " <<i<<i<<"  "<<i<<i<<"  "<<i<<i<< "     " <<i<<i<<"                                    " << char1 << endl;

	cout << "\t      " << char5 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char3 << char6 << endl;
	textcolor(white);

	gotoxy(42,5);

	textcolor(brown);
	for (size_t k = 0; k < 30; k++) {
			cout << i ;
	}

	gotoxy(48,4);
	cout << "AGENCIA DE VIAJENS";

	textcolor(white);

	gotoxy(0,8);

}

void configurar_terminal(){
	//Definir nome janela
	system("TITLE AGENCIA DE VIAGENS");

	//Ajustar tamanho janela

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT sr;
	COORD consoleSize;

	consoleSize.X = 90; consoleSize.Y = 25;

	sr.Top = sr.Left = 0;
	sr.Right = 89; sr.Bottom = 24;

	SetConsoleWindowInfo(console, TRUE, &sr);
	SetConsoleScreenBufferSize(console, consoleSize);

}

void gotoxy(int x, int y){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	_COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(hConsole, pos);
}

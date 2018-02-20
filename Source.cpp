#include <iostream>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <stdlib.h>
using namespace std;
//clasa proiectil
class Proiectil
{
private:
	int x, y, originalX, originalY;	
public:
	//constructor implicit
	Proiectil()
	{
		x = y = originalX = originalY = 0;
	}
	//constructor cu parametrii
	Proiectil(int x, int y)
	{
		this->x = x;
		this->y = y;
		this->originalX = x;
		this->originalY = y;
	}
	//resetare pozitie proiectil
	void ResetP()
	{
		this->x = this->originalX;
		this->y = this->originalY;	
	}
	//getteri pentru coordonate proiectil
	inline int getX() { return this->x; } inline int getY() { return this->y; }
	//avansare proiectil
	void Misca()
	{	
		(this->y)--;		
	}
	//miscare proiectil dupa nava
	inline void SusP() { (this->y)--; }
	inline void JosP() { (this->y)++; }
	inline void StangaP() { (this->x)--; }
	inline void DreaptaP() { (this->x)++; }
};
//clasa nava
class Nava
{
public:
	int x, y, originalXN, originalYN;
public:
	//constructor implicit 
	Nava()
	{
		x = y = 0;
	}
	//constructor cu parametrii
	Nava(int x, int y) :Nava()
	{
		this->x = x;
		this->y = y;
		this->originalXN = x;
		this->originalYN = y;
	}
	//resetare pozitie nava
	inline void ResetN()	{ this->x = this->originalXN; this->y = this->originalYN; }
	//getteri pentru coordonate nava
	inline int getXN() { return this->x; } inline int getYN() { return this->y; }
	//miscare nava
	inline void Stanga() { (this->x)--; } inline void Dreapta() { (this->x)++; }
	inline void Sus() { (this->y)--; } inline void Jos() { (this->y)++; }
};
//clasa inamic
class Inamic
{
private:
	int x, y, originalXI, originalYI;
public:
	//constructor cu parametrii
	Inamic(int x, int y)
	{
		this->x = x;
		this->y = y;
		this->originalXI = x;
		this->originalYI = y;
	}
	//resetare pozitie inamic intre limitele hartii
	inline void ResetI() { srand(time(NULL)); this->x = ((rand() % 37) + 1); this->y = ((rand() % 10) + 0); }
	//getteri coordonate inamic
	inline int getXI() { return this->x; } inline int getYI() { return this->y; }
};
//clasa manage
class Manage
{
private:
	const int latime = 40 , lungime =20;
	int scor;
	char stanga, dreapta,sus, jos;
	bool exit;
	Proiectil * proiectil;
	Nava * nava;
	Inamic * inamic;
public:
	//constructor cu parametrii
	Manage()
	{
		this->scor = 0;
		this->stanga = 'a';
		this->dreapta = 'd';
		this->sus = 'w';
		this->jos = 's';
		this->exit = false;
		this->proiectil = new Proiectil(((this->latime) / 2), ((this->lungime)-3));
		this->nava = new Nava((this->latime)/2, (this->lungime)-2);
		srand(time(NULL));
		this->inamic = new Inamic(rand()%(this->latime-3)+1, rand()%(this->lungime/2)+0);
	}
	//destructor
	~Manage()
	{
		if (this->inamic!= NULL)
			delete this->inamic;
		if (this->nava != NULL)
			delete this->nava;
		if (this->proiectil != NULL)
			delete this->proiectil;
	}
	//harta propriu zisa
	void Desen()
	{
		//curatare consola
		system("cls");
		//perete superior
		for (int i = 0; i < this->latime + 2; i++)	
			cout << "\xDB";
		cout << endl;
		for (int i = 0; i < this->lungime; i++)
		{
			for (int j = 0; j < this->latime; j++)
			{
				//coordonate obiecte
				int navaX = this->nava->getXN();
				int navaY = this->nava->getYN();
				int inamicX = this->inamic->getXI();
				int inamicY = this->inamic->getYI();
				int proiectilX = this->proiectil->getX();
				int proiectilY = this->proiectil->getY();
				//perete lateral stanga
				if (j == 0)
					cout << "\xDB";
				//mijloc nava
				if (navaX == j && navaY == i)
					cout << "N";
				//varf nava
				else if (navaX == j && navaY == i + 1)
					cout << "^";
				//proiectil
				else if (proiectilX == j && proiectilY == i)
					cout << "|";				
				//aripa stanga
				else if (navaX == j + 1 && navaY == i)
					cout << "<";
				//aripa dreapta
				else if (navaX == j - 1 && navaY == i)
					cout << ">";
				//inamic
				else if (inamicX == j && inamicY == i)
					cout << "I";
				//golul hartii
				else
					cout << " ";
				//perete lateral dreapta
				if (j == (this->latime) - 1)
					cout << "\xDB";
			}
			//asezare pe vertical
			cout << endl;
		}
		//perete inferior
		for (int i = 0; i < this->latime + 2; i++)
			cout << "\xDB";
		cout << endl;
	}
	void Imput()
	{
		this->proiectil->Misca();
		//coordonate
		int navaX = this->nava->getXN();
		int navaY = this->nava->getYN();
		int inamicX = this->inamic->getXI();
		int inamicY = this->inamic->getYI();
		int proiectilX = this->proiectil->getX();
		int proiectilY = this->proiectil->getY();

		//fizici
		if (_kbhit())
		{
			//memorare tasta apasate
			char caracter = _getch();
			//miscare nava in sus cu proiectilul incarcat
			if (caracter == this->sus)
			if (navaY > 1)
			if ((proiectilX == navaX) && (proiectilY == navaY - 1))
			{
				this->nava->Sus();
				this->proiectil->SusP();
			}
			//miscare nava in jos cu proiectilul incarcat
			if (caracter == this->jos)
			if (navaY + 1< this->lungime)
			if ((proiectilX == navaX) && (proiectilY == navaY - 1))
			{
				this->nava->Jos();
				this->proiectil->JosP();
			}	
			//miscare nava in stanga cu proiectilul incarcat
			if (caracter == this->stanga)
			if (navaX > 1)
			if ((proiectilX == navaX) && (proiectilY == navaY - 1))
			{
				this->nava->Stanga();
				this->proiectil->StangaP();
			}		
			//miscare nava in dreapta cu proiectilul incarcat
			if (caracter == this->dreapta)
			if (navaX < this->latime - 2)
			if ((proiectilX == navaX) && (proiectilY == navaY - 1))
			{
				this->nava->Dreapta();
				this->proiectil->DreaptaP();
			}
			//miscare nava in sus fara proiectil
			if (caracter == this->sus)
			if (navaY > 1)
			if ((proiectilX != navaX))
			{
				this->nava->Sus();
			}
			//miscare nava in jos fara proiectil
			if (caracter == this->jos)
			if (navaY + 1< this->lungime)
			if ((proiectilX != navaX))
			{
				this->nava->Jos();
			}
			//miscare nava in stanga fara proiectil
			if (caracter == this->stanga)
			if (navaX > 1)
			if ((proiectilY != navaY - 1))
			{
				this->nava->Stanga();
			}
			//miscare nava in dreapta fara proiectil
			if (caracter == this->dreapta)
			if (navaX < this->latime - 2)
			if ((proiectilY != navaY - 1))
			{
				this->nava->Dreapta();
			}	
			//jos pe aceeasi linie cu proiectilul
			if (caracter == this->jos)
			if (navaY + 1< this->lungime)
			if ((proiectilY != navaX))
			{
				this->nava->Jos();
			}//sus pe aceeasi linie cu proiectilul
			if (caracter == this->sus)
			if (navaY > 1)
			if ((proiectilY != navaX))
			{
				this->nava->Sus();
			}
			//iesire joc
			if (caracter == 'q')
			{
				cout << "GAME OVER!" << endl;
				cout << "SCORE: " << this->scor << endl;
				Sleep(2000);
				this->exit = true;
			}
		}
	}
	void Logica()
	{
		//coordonate
		int navaX = this->nava->getXN();
		int navaY = this->nava->getYN();
		int inamicX = this->inamic->getXI();
		int inamicY = this->inamic->getYI();
		int proiectilX = this->proiectil->getX();
		int proiectilY = this->proiectil->getY();

		//reset proiectil cand loveste un perete
		if (proiectilY == -1)
		{
			int x, y;
			x = this->nava->getXN();
			y = this->nava->getYN();
			this->proiectil = new Proiectil(x, y-1);
		}
		//coliziune proiectil cu inamic plus respawn proiectil in nava
		if ((proiectilX == inamicX) && (proiectilY == inamicY))
		{			
			scor++;
			this->inamic->ResetI();
			int x, y;
			x = this->nava->getXN();
			y = this->nava->getYN();
			this->proiectil = new Proiectil(x, y - 1);
		}
		//coliziune mijloc nava
		if ((navaX == inamicX) && (navaY == inamicY))
		{
			cout << "GAME OVER!" << endl;
			cout << "SCORE: " << this->scor << endl;
			Sleep(2000);			
				this->exit = true;
		}
		//coliziune aripa dreapta
		if (((navaX + 1) == inamicX) && (navaY == inamicY))
		{
			cout << "GAME OVER!" << endl;
			cout << "SCORE: " << this->scor << endl;
			Sleep(2000);		
			this->exit = true;
		}		
		//coliziune aripa stanga 
		if (((navaX - 1) == inamicX) && (navaY == inamicY))
		{
			cout << "GAME OVER!" << endl;
			cout << "SCORE: " << this->scor << endl;
			Sleep(2000);		
			this->exit = true;
		}
		//coliziune bord
		if ((navaX == inamicX) && ((navaY-1) == inamicY))
		{
			cout << "GAME OVER!" << endl;
			cout << "SCORE: " << this->scor << endl;
			Sleep(2000);		
			this->exit = true;
		}
	}
	//functie joc
	void Run()
	{
		while (!exit)
		{
			Desen();
			Imput();
			Logica();
			cout << "COMANDS: ";
			cout << "|| UP = w || ";
			cout << "DOWN = s || ";
			cout << "RIGHT = d || ";
			cout << "LEFT = a || ";
			cout << "EXIT = q ||" << endl;
			cout << "SCORE: " << this->scor << endl;
		}
	}


};
int main()
{
	Manage game;
	game.Run();
	return 0;
}
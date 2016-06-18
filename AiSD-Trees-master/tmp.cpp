


void rotacja_w_prawo(T wrt)
{
	listek<T>*      akt = szukaj(wrt);
	if (akt != nullptr)        rotacja_w_prawo(akt);
} //po wartoœci


void rotacja_w_lewo(T wrt)
{
	listek<T>* akt = szukaj(wrt);
	if (akt != nullptr)       rotacja_w_lewo(akt);
} //po wartoœci

void rotacja_w_prawo(listek<T>* nizszy) //podajemy wêze³ ni¿szy, który chcemy podnieœæ w górê
{
	listek<T>* wyzszy = nizszy->rodzic;
	listek<T>* tmp = nullptr;
	if (wyzszy != nullptr && wyzszy->rodzic != nullptr)
		tmp = wyzszy->rodzic;
	if (wyzszy != nullptr && wyzszy->lewy != nullptr)
		nizszy = wyzszy->lewy;
	else return;
	wyzszy->lewy = nizszy->prawy;
	if (wyzszy->lewy != nullptr)
		wyzszy->lewy->rodzic = wyzszy;
	nizszy->prawy = wyzszy;
	nizszy->rodzic = wyzszy->rodzic;
	wyzszy->rodzic = nizszy;
	if (tmp != nullptr){
		if (tmp->lewy == wyzszy) tmp->lewy = nizszy;
		else tmp->prawy = nizszy;
		return;
	}
	else
	{
		if (Root != nullptr)       Root = nizszy;
	}
} //po adresie

void rotacja_w_lewo(listek<T>* nizszy) //podajemy wêze³ ni¿szy, który chcemy opuœciæ
{
	listek<T>* wyzszy = nizszy->rodzic;
	if (wyzszy != nullptr && wyzszy->prawy != nullptr) 
		nizszy = wyzszy->prawy;
	else return;
	listek<T>* tmp = wyzszy->rodzic;
	wyzszy->prawy = nizszy->lewy;
	if (wyzszy->prawy != nullptr)
		wyzszy->prawy->rodzic = wyzszy;
	nizszy->lewy = wyzszy;
	nizszy->rodzic = tmp;
	wyzszy->rodzic = nizszy;
	if (tmp != nullptr){
		if (tmp->lewy == wyzszy) tmp->lewy = nizszy;
		else tmp->prawy = nizszy;
	}
	else{ if (Root != nullptr) Root = nizszy; }
} // po adresie






void Och_Och_Tak_Strasznie_Chce_Byc_Lista()
{
	while (Root->lewy != nullptr)
	{
		listek<T>* akt = Root;
		while (akt->lewy != nullptr)
		{
			rotacja_w_prawo(akt->lewy);
			while (akt->lewy == nullptr)
			{
				if (akt->prawy != nullptr)     
					akt = akt->prawy;
				else break;
			}
		}
	}
}


void Teraz_Tak_Strasznie_Chcialbym_Byc_Normalny() //check
{
	Och_Och_Tak_Strasznie_Chce_Byc_Lista();
	int j = 1;
	int z = pow(2, log2(licznosc_calego()));
	for (j; j <= z; j++)
	{
		int i = 1; listek<T>* akt = Root;
		while (1)
		{
			if (i++ % 2 == 0) { rotacja_w_lewo(akt); }
			if (akt->prawy != nullptr)      
				akt = akt->prawy;
			else break;
		}
	}
	Root = Root->lewy;
	Dodaj(Root->rodzic->wartosc);
	delete Root->rodzic;
	Root->rodzic = nullptr;
}


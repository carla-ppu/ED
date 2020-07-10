#ifndef _SISTEMA_VENTAS_H
#define _SISTEMA_VENTAS_H

#include "lista.h"
#include <string>
#include "Diccionario.h"
#include "DiccionarioHash.h"

using namespace std;

/*
Excepciones levantadas por las operaciones 
*/
class EAltaNoAdmitida {};
class EConciertoExistente {};
class EEsperaNoAdmitida {};
class EConciertoInexistente {};
class EClienteInexistente {};
class EConciertoSinEsperas {};
class EConciertoConEsperas {};

class Cliente {
public:
	string _concierto;
	Lista<string>::Iterator _pos_cliente;
	Lista<string>::Iterator _pos_lista_espera;
	bool esta_concierto;
	Cliente(const Lista<string>::Iterator& pos_cliente, const string& concierto, const Lista<string>::Iterator& pos_lista_espera) 
		:_pos_cliente(pos_cliente), _concierto(concierto), _pos_lista_espera(pos_lista_espera) {
		//esta_concierto = false;
	};
	//Cliente();
	//Diccionario<string, Lista<string>::Iterator> it_lista_espera;
};

class Concierto {
public:
	
	Lista<string>::Iterator _pos_concierto;
	Lista<string> _lista_espera;
	Concierto(const Lista<string>::Iterator& pos_concierto) :_pos_concierto(pos_concierto) {};
	//Concierto();
	
	//clave: cliente, valor: it a lista espera
};


class SistemaVentas {
public:

	/*
	Operaci�n constructora que crea un sistema de gesti�n de venta de entradas vac�o.
	*/
	SistemaVentas();


	/*
	A�ade un nuevo concierto al sistema, con c�digo de identificaci�n 'c�digo_concierto'.
	Si ya est� dado de alta un concierto con dicho c�digo, la operaci�n lanzar� una excepci�n EConciertoExistente.
	*/
	void an_concierto(const string&  codigo_concierto);

	
	/*
	A�ade un nuevo cliente al sistema con c�digo de identificaci�n 'codigo_cliente', 
	y lo pone a la espera de compra de entradas para el concierto con c�digo de indentificaci�n 'codigo_concierto'. 
	En caso de que no exista el cliente, o no exista el concierto, la operaci�n lanzar� una excepci�n EAltaNoAdmitida.
	*/
	void an_cliente(const string&  codigo_cliente, const string& codigo_concierto);
	
	
	/*
	Elimina el concierto con c�digo de identificaci�n 'codigo_concierto' del sistema.
	Para ello dicho concierto debe existir; si no es as�, la operaci�n lanzar� una excepci�n EConciertoInexistente.
	As� mismo, su lista de espera debe estar vac�a; en otro caso, la operaci�n lanzar� una excepci�n EConciertoConEsperas.
	*/
	void borra_concierto(const string& codigo_concierto);

	
	/*
	Elimina todo rastro del cliente con c�digo de identificaci�n 'codigo_cliente' del sistema.
	Si el cliente no existe, la operaci�n lanzar� una excepci�n EClienteInexistente.
	*/
	void borra_cliente(const string& codigo_concierto);


	/*
	Devuelve cierto si hay clientes a la espera de comprar entradas para el concierto 'codigo_concierto', y falso en otro caso.
	El c�digo del concierto debe existir; si no, la operaci�n lanzar� un excepci�n EConciertoInexistente.
	*/
	bool hay_clientes_en_espera(const string& codigo_concierto) const;

	
	/*
	Devuelve el c�digo del primer cliente en la lista de espera para el concierto 'codigo_concierto'.
	Si no existe un concierto con el c�digo dado, la operaci�n lanzar� una excepci�n EConciertoInexistente.	
	Si el concierto existe pero no tiene lista de espera, la operaci�n lanzar� una excepci�n EConciertoSinEsperas.
	*/
	const string& proximo_cliente(const string& codigo_concierto) const;
	
	
	/* 
	Realiza la venta de entrada para el concierto 'codigo_concierto'. 
	Para ello, elimina el primer cliente de la lista de espera, y dicho cliente queda en disposici�n de realizar nuevas compras. 
	Lanzar� la excepci�n EConciertoInexistente en caso de que el concierto con codigo 'codigo_concierto' no exista. 
	Lanzar� la excepci�n EConciertoSinEsperas en caso de que el concierto exista pero no tenga lista de espera.
	*/
	void venta(const string& codigo_concierto); 
	
	
	/*
	 Registra el abandono, por parte del cliente 'codigo_cliente', de la lista donde se encuentra esperando. 
	 Como consecuencia, el cliente se elimina de dicha lista de espera y el cliente pasa a estar en diposici�n de realizar 
	 nuevas compras. 
	 Se lanzar� la excepcion EClienteInexistente en caso de que el cliente no exista.
	 Si el cliente existe pero no se encuentra esperando en ninguna lista de espera, la operaci�n no tendr� efecto.
	*/
	void abandona(const string& codigo_cliente);

	
	/*
	Pone al cliente 'codigo_cliente' en espera para comprar una entrada en el concierto 'codigo_concierto'. 
	El sistema admite �nicamente que un cliente est� esperando para comprar entradas en, a lo sumo, un concierto. 
	La operaci�n elevar� una excepci�n EEsperaNoAdmitida si no existe un cliente con c�digo 'codigo_cliente', 
	si no existe un concierto con c�digo 'codigo_concierto' o si el cliente est� ya en una lista de espera.
	*/
	void pon_en_espera(const string& codigo_cliente, const string & codigo_concierto);

	
	/*
	Devuelve una lista, ordenada alfab�ticamente, con los c�digos de los clientes registrados en el sistema.
	*/
	Lista<string> clientes() const;

	
	/*
	Devuelve el n�mero de clientes registrados en el sistema.
	*/
	unsigned int num_clientes() const;

	
	/*
	Devuelve el n�mero de conciertos registrados en el sistema.  
	*/
	unsigned int num_conciertos() const;


private:
	/*** Incluir todos los detalles de representaci�n que se consideren oportunos */
	DiccionarioHash<string, Concierto> _concierto; //concierto, clase concierto
	Diccionario<string, Cliente>  _cliente; //cliente, clase concierto
	Lista<string> _lista_cliente;
	Lista<string> _lista_concierto;
};

#endif
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
	Operación constructora que crea un sistema de gestión de venta de entradas vacío.
	*/
	SistemaVentas();


	/*
	Añade un nuevo concierto al sistema, con código de identificación 'código_concierto'.
	Si ya está dado de alta un concierto con dicho código, la operación lanzará una excepción EConciertoExistente.
	*/
	void an_concierto(const string&  codigo_concierto);

	
	/*
	Añade un nuevo cliente al sistema con código de identificación 'codigo_cliente', 
	y lo pone a la espera de compra de entradas para el concierto con código de indentificación 'codigo_concierto'. 
	En caso de que no exista el cliente, o no exista el concierto, la operación lanzará una excepción EAltaNoAdmitida.
	*/
	void an_cliente(const string&  codigo_cliente, const string& codigo_concierto);
	
	
	/*
	Elimina el concierto con código de identificación 'codigo_concierto' del sistema.
	Para ello dicho concierto debe existir; si no es así, la operación lanzará una excepción EConciertoInexistente.
	Así mismo, su lista de espera debe estar vacía; en otro caso, la operación lanzará una excepción EConciertoConEsperas.
	*/
	void borra_concierto(const string& codigo_concierto);

	
	/*
	Elimina todo rastro del cliente con código de identificación 'codigo_cliente' del sistema.
	Si el cliente no existe, la operación lanzará una excepción EClienteInexistente.
	*/
	void borra_cliente(const string& codigo_concierto);


	/*
	Devuelve cierto si hay clientes a la espera de comprar entradas para el concierto 'codigo_concierto', y falso en otro caso.
	El código del concierto debe existir; si no, la operación lanzará un excepción EConciertoInexistente.
	*/
	bool hay_clientes_en_espera(const string& codigo_concierto) const;

	
	/*
	Devuelve el código del primer cliente en la lista de espera para el concierto 'codigo_concierto'.
	Si no existe un concierto con el código dado, la operación lanzará una excepción EConciertoInexistente.	
	Si el concierto existe pero no tiene lista de espera, la operación lanzará una excepción EConciertoSinEsperas.
	*/
	const string& proximo_cliente(const string& codigo_concierto) const;
	
	
	/* 
	Realiza la venta de entrada para el concierto 'codigo_concierto'. 
	Para ello, elimina el primer cliente de la lista de espera, y dicho cliente queda en disposición de realizar nuevas compras. 
	Lanzará la excepción EConciertoInexistente en caso de que el concierto con codigo 'codigo_concierto' no exista. 
	Lanzará la excepción EConciertoSinEsperas en caso de que el concierto exista pero no tenga lista de espera.
	*/
	void venta(const string& codigo_concierto); 
	
	
	/*
	 Registra el abandono, por parte del cliente 'codigo_cliente', de la lista donde se encuentra esperando. 
	 Como consecuencia, el cliente se elimina de dicha lista de espera y el cliente pasa a estar en diposición de realizar 
	 nuevas compras. 
	 Se lanzará la excepcion EClienteInexistente en caso de que el cliente no exista.
	 Si el cliente existe pero no se encuentra esperando en ninguna lista de espera, la operación no tendrá efecto.
	*/
	void abandona(const string& codigo_cliente);

	
	/*
	Pone al cliente 'codigo_cliente' en espera para comprar una entrada en el concierto 'codigo_concierto'. 
	El sistema admite únicamente que un cliente esté esperando para comprar entradas en, a lo sumo, un concierto. 
	La operación elevará una excepción EEsperaNoAdmitida si no existe un cliente con código 'codigo_cliente', 
	si no existe un concierto con código 'codigo_concierto' o si el cliente está ya en una lista de espera.
	*/
	void pon_en_espera(const string& codigo_cliente, const string & codigo_concierto);

	
	/*
	Devuelve una lista, ordenada alfabéticamente, con los códigos de los clientes registrados en el sistema.
	*/
	Lista<string> clientes() const;

	
	/*
	Devuelve el número de clientes registrados en el sistema.
	*/
	unsigned int num_clientes() const;

	
	/*
	Devuelve el número de conciertos registrados en el sistema.  
	*/
	unsigned int num_conciertos() const;


private:
	/*** Incluir todos los detalles de representación que se consideren oportunos */
	DiccionarioHash<string, Concierto> _concierto; //concierto, clase concierto
	Diccionario<string, Cliente>  _cliente; //cliente, clase concierto
	Lista<string> _lista_cliente;
	Lista<string> _lista_concierto;
};

#endif
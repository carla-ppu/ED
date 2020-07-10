#include "SistemaVentas.h"

/*
 COMPLEJIDAD:
 
*/
SistemaVentas::SistemaVentas() {
			/*  A IMPLEMENTAR */
}


/*
 COMPLEJIDAD:
 
*/
void SistemaVentas::an_concierto(const string &  codigo_concierto){
			/*  A IMPLEMENTAR */
	DiccionarioHash<string, Concierto>::Iterator iconcierto = _concierto.busca(codigo_concierto);

	if (iconcierto != _concierto.end()) throw EConciertoExistente();
	else {

		_lista_concierto.pon_ppio(codigo_concierto);
		_concierto.inserta(codigo_concierto, Concierto(_lista_concierto.begin()));
		//iconcierto.valor()._pos_concierto = _lista_concierto.begin();
	}
}


/*
 COMPLEJIDAD:
 
*/
void SistemaVentas::an_cliente(const string &  codigo_cliente, const string& codigo_concierto){
			/*  A IMPLEMENTAR */
	DiccionarioHash<string, Concierto>::Iterator iconcierto = _concierto.busca(codigo_concierto);
	if (iconcierto == _concierto.end()) throw EAltaNoAdmitida();
	else {
		Diccionario<string, Cliente>::Iterator icliente = _cliente.busca(codigo_cliente);
		if (icliente != _cliente.end()) throw EAltaNoAdmitida();
		else {
			iconcierto.valor()._lista_espera.pon_ppio(codigo_cliente);
			_lista_cliente.pon_ppio(codigo_cliente);
			_cliente.inserta(codigo_cliente, Cliente(_lista_cliente.begin(), iconcierto.clave(), iconcierto.valor()._lista_espera.begin()));
				/*pon_en_espera(codigo_cliente, codigo_concierto);*/
			
			

		}
	}
}


/*
 COMPLEJIDAD:
 
*/
void SistemaVentas::borra_concierto(const string &  codigo_concierto) {
			/*  A IMPLEMENTAR */
	DiccionarioHash<string, Concierto>::Iterator iconcierto = _concierto.busca(codigo_concierto);
	if (iconcierto == _concierto.end()) throw EConciertoInexistente();
	if (!iconcierto.valor()._lista_espera.esVacia()) throw EConciertoConEsperas();

	_lista_concierto.eliminar(iconcierto.valor()._pos_concierto);
	_concierto.borra(codigo_concierto);
}


/*
 COMPLEJIDAD:
 
*/
void SistemaVentas::borra_cliente(const string &  codigo_cliente) {
			/*  A IMPLEMENTAR */
	Diccionario<string, Cliente>::Iterator icliente = _cliente.busca(codigo_cliente);
	if (icliente == _cliente.end()) throw EClienteInexistente();

	
	/*Diccionario<string, Lista<string>::Iterator>::Iterator it = _cliente.busca(codigo_cliente).valor().it_lista_espera.busca(codigo_cliente);
	Diccionario<string, Lista<string>::Iterator>::Iterator it_end = _cliente.busca(codigo_cliente).valor().it_lista_espera.end();*/
		
		DiccionarioHash<string, Concierto>::Iterator iconcierto = _concierto.busca(icliente.valor()._concierto);
		if (icliente.valor()._pos_lista_espera != iconcierto.valor()._lista_espera.end()) {

			string concierto = iconcierto.clave();
			iconcierto.valor()._lista_espera.eliminar(icliente.valor()._pos_lista_espera);
		}
		
		_lista_cliente.eliminar(icliente.valor()._pos_cliente);
		_cliente.borra(codigo_cliente);
	}
	


	

/*
 COMPLEJIDAD:
 
*/
bool SistemaVentas::hay_clientes_en_espera(const string & codigo_concierto) const{
			/*  A IMPLEMENTAR */
	DiccionarioHash<string, Concierto>::ConstIterator iconcierto = _concierto.cbusca(codigo_concierto);
	if (iconcierto == _concierto.cend()) throw EConciertoInexistente();
	if (iconcierto.valor()._lista_espera.esVacia()) return false;
	else return true;
}


/*
 COMPLEJIDAD:
 
*/
const string& SistemaVentas::proximo_cliente(const string & codigo_concierto) const{
			/*  A IMPLEMENTAR */
	DiccionarioHash<string, Concierto>::ConstIterator iconcierto = _concierto.cbusca(codigo_concierto);
	if (iconcierto == _concierto.cend()) throw EConciertoInexistente();

	if (iconcierto.valor()._lista_espera.esVacia()) throw EConciertoSinEsperas();

	return iconcierto.valor()._lista_espera.ultimo();
}


/*
 COMPLEJIDAD:
 
*/
void SistemaVentas::venta(const string& codigo_concierto) {
	/*  A IMPLEMENTAR */
	DiccionarioHash<string, Concierto>::Iterator iconcierto = _concierto.busca(codigo_concierto);

	if (iconcierto == _concierto.end()) throw EConciertoInexistente();

	if (iconcierto.valor()._lista_espera.esVacia()) throw EConciertoSinEsperas();
	//Diccionario<string, Lista<string>::Iterator>::Iterator it = _concierto.busca(codigo_concierto).valor().it_lista_espera.busca();
	
	string cliente = iconcierto.valor()._lista_espera.ultimo();
	//IMPORTANTE!!!!!!!!!!
	_cliente.busca(cliente).valor()._pos_lista_espera = iconcierto.valor()._lista_espera.end();
	iconcierto.valor()._lista_espera.quita_final();
	
}

/*
 COMPLEJIDAD:
 
*/
void SistemaVentas::abandona(const string& codigo_cliente) {
			/*  A IMPLEMENTAR */
	Diccionario<string, Cliente>::Iterator icliente = _cliente.busca(codigo_cliente);
		if (icliente == _cliente.end()) throw EClienteInexistente();
		else {
			
			if (icliente.valor()._pos_lista_espera != _concierto.busca(icliente.valor()._concierto).valor()._lista_espera.end()) {
				_concierto.busca(icliente.valor()._concierto).valor()._lista_espera.eliminar(icliente.valor()._pos_lista_espera);
				icliente.valor()._pos_lista_espera = _concierto.busca(icliente.valor()._concierto).valor()._lista_espera.end();
				
		}
	}

}


/*
 COMPLEJIDAD:
 
*/
void SistemaVentas::pon_en_espera(const string & codigo_cliente, const string & codigo_concierto){
			/*  A IMPLEMENTAR */
	Diccionario<string, Cliente>::Iterator icliente = _cliente.busca(codigo_cliente);
	DiccionarioHash<string, Concierto>::Iterator iconcierto = _concierto.busca(codigo_concierto);


	if (icliente == _cliente.end() || iconcierto == _concierto.end() || 
		icliente.valor()._pos_lista_espera != iconcierto.valor()._lista_espera.end()) throw EEsperaNoAdmitida();
	else {

		iconcierto.valor()._lista_espera.pon_ppio(codigo_cliente);
		icliente.valor()._pos_lista_espera = iconcierto.valor()._lista_espera.begin();
	}
	
	
}


/*
 COMPLEJIDAD:
 
*/
Lista<string> SistemaVentas::clientes() const {
			/*  A IMPLEMENTAR */
	Lista<string> l;
	Diccionario<string, Cliente>::ConstIterator ini = _cliente.cbegin();
	Diccionario<string, Cliente>::ConstIterator fin = _cliente.cend();

	while (ini != fin) {

		l.pon_final(ini.clave());
		ini.next();

	}
	return l;
}


/*
 COMPLEJIDAD:
 
*/
unsigned int SistemaVentas::num_clientes() const {
			/*  A IMPLEMENTAR */
	return _lista_cliente.longitud();
}


/*
 COMPLEJIDAD:
 
*/
unsigned int SistemaVentas::num_conciertos() const {
			/*  A IMPLEMENTAR */
	return _lista_concierto.longitud();
}

#include "Racional.h"
#include <cmath>

  //Metodos publicos

  	//**** COMPLETAR
	//  Deben implementarse los metodos publicos de la clase
	//****
Racional::Racional(long n, long d) {
	if (d == 0) throw EDenominadorCero();
	_numer = n;
	_denom = d;
	this->reduce();
 }
Racional::Racional() {
	_numer = 0;
	_denom = 1;
 }
Racional Racional::suma(const Racional& r){
	
	long min = Racional::mcm(_denom, r._denom);
	return Racional((_numer * min) / _denom + (r._numer * min) / r._denom, min);
}
Racional Racional::operator-(const Racional& r) const {

	long min = Racional::mcm(_denom, r._denom);
	return Racional((_numer * min) / _denom - (r._numer * min) / r._denom, min);
	
}

Racional& Racional::operator *=(const Racional& r) {
	_numer = _numer * r._numer;
	_denom = _denom * r._denom;
	this->reduce();
	return *this;
}

Racional& Racional::divideYActualiza(const Racional& r) {
	//if (r._denom == 0) throw EDenominadorCero();
	if (r._numer == 0 && r._denom == 1) {
		 throw EDivisionPorCero();
	}
	_numer =_numer * r._denom; 
	_denom = _denom * r._numer; 
	this->reduce();
	return *this;

}

bool Racional::operator==(const Racional& r) {
	return (_numer == r._numer && _denom == r._denom);
}

  // Funciones amigas
ostream& operator<<(ostream& out, const Racional& f) {
	out << f._numer << "/" << f._denom;
	return out;
}

 // Metodos privados
void Racional::reduce() {
	  // Se asegura que el denominador siempre sea positivo   
	if (_denom < 0) {
		_numer = -_numer;
		_denom = -_denom;
	}
	  // Se divide numerador y denominador por el maximo comun divisor de ambos
	long fsimp = mcd(_numer, _denom);
	_numer /= fsimp;
	_denom /= fsimp;
}

long Racional::mcd(long v1, long v2) {
	  // El calculo del maximo comun divisor se hace por el algoritmo de Euclides
	v1 = abs(v1); 
    v2 = abs(v2);	
	if (v1 < v2) {
		long tmp = v1;
		v1 = v2;
		v2 = tmp;
	}
	while (v2 != 0) {
		long nv2 = v1%v2;
		v1 = v2;
		v2 = nv2;
	}
	return v1;
}

long Racional::mcm(long v1, long v2) {
	return v1*v2 / mcd(v1, v2);
}


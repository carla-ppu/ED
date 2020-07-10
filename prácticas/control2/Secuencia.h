using namespace std;

#ifndef _SECUENCIA_H_
#define _SECUENCIA_H_

/// Excepción de elemento inexistente
class ElementoInvalido {};


template<class T>
class Secuencia {
public:
	static const int MAX = 2;
	Secuencia() {
		// A IMPLEMENTAR
		_v = new T[MAX];
		_tam = MAX;
		_numElem = 0;
	}

	void pon(const T& e) {
		// A IMPLEMENTAR
		if (_tam == MAX) {
			T* viejo = _v;
			_tam *= 2;
			_v = new T[_tam];
			for (int i= 0; i < _numElem; i++) {
				_v[i] = viejo[i];
			}
			
			delete[] viejo;
		}
		_v[_numElem] = e;
		_numElem++;
	}

	const T& elem(int i) {
		// A IMPLEMENTAR
		if (i >= _numElem) throw ElementoInvalido();
		return _v[i];
	}

	int num_elems() const {
		// A IMPLEMENTAR
		return _numElem;
	}

     // DEBEN INCLUIRSE E IMPLEMENTARSE 
	 // LAS OPERACIONES ADICIONALES
	 // NECESARIAS PARA GARANTIZAR EL CORRECTO
	 // FUNCIONAMIENTO DEL TAD
	//COPIA
	Secuencia(const Secuencia<T>& s) {
		copia(s);
	}
	//ASIGNACIÓN
	Secuencia<T> operator=(const Secuencia<T>& e) {
		if (this != &e) {
			borra();
			copia(e);
		}
		return *this;
	}
	//DESTRUCTOR
	~Secuencia() {
		borra();
	}


private:
  // INCLUIR DETALLES DE REPRESENTACION Y OPERACIONES AUXILIARES
	T* _v;
	int _tam;
	int _numElem;

	void borra() {
		delete[] _v;
	}

	void copia(const Secuencia<T>& s) {
		_tam = s._tam + MAX;
		_numElem = s._numElem;
		_v = new T[_tam];
		for (int i = 0; i < _numElem; i++) {
			_v[i] = s._v[i];
		}
	}
};


#endif



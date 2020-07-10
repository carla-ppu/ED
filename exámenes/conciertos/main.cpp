#include "SistemaVentas.h"
#include "lista.h"
#include <iostream>
#include <string>
using namespace std;

void lista(const Lista<string>& l) {
	Lista<string>::ConstIterator i = l.cbegin();
	while (i != l.cend()) {
		cout << i.elem() << " ";
		i.next();
	}
}

void an_cliente(SistemaVentas& ventas) {
   string codigo_cliente;
   cin >> codigo_cliente;
   string codigo_concierto;
   cin >> codigo_concierto;
   cout << "an_cliente " << codigo_cliente << " " << codigo_concierto << " => ";
   try {
     ventas.an_cliente(codigo_cliente,codigo_concierto);
     cout << "OK" << endl;
   }   
   catch(EAltaNoAdmitida) {
	   cout << "ALTA_NO_ADMITIDA" << endl;
   }
 
}

void borra_cliente(SistemaVentas& ventas) {
	string codigo_cliente;
	cin >> codigo_cliente;
	cout << "borra_cliente " << codigo_cliente <<  " => ";
	try {
		ventas.borra_cliente(codigo_cliente);
		cout << "OK" << endl;
	}
	catch (EClienteInexistente) {
		cout << "CLIENTE_NO_EXISTE" << endl;
	}

}

void borra_concierto(SistemaVentas& ventas) {
	string codigo_concierto;
	cin >> codigo_concierto;
	cout << "borra_concierto " << codigo_concierto << " => ";
	try {
		ventas.borra_concierto(codigo_concierto);
		cout << "OK" << endl;
	}
	catch (EConciertoInexistente) {
		cout << "CONCIERTO_NO_EXISTE" << endl;
	}
	catch (EConciertoConEsperas) {
		cout << "CONCIERTO_CON_ESPERAS" << endl;
	}

}


void an_concierto(SistemaVentas& ventas) {
	string codigo_concierto;
	cin >> codigo_concierto;
	cout << "an_concierto " << codigo_concierto << " => ";
	try {
		ventas.an_concierto(codigo_concierto);
		cout << "OK" << endl;
	}
	catch (EConciertoExistente) {
		cout << "CONCIERTO_YA_EXISTE" << endl;
	}

}

void pon_en_espera(SistemaVentas& ventas) {
	string codigo_cliente;
	string codigo_concierto;
	cin >> codigo_cliente;
	cin >> codigo_concierto;
	cout << "pon_en_espera " << codigo_cliente << " " << codigo_concierto << " => ";
	try {
		ventas.pon_en_espera(codigo_cliente,codigo_concierto);
		cout << "OK" << endl;
	}
	catch (EEsperaNoAdmitida) {
		cout << "ESPERA_NO_ADMITIDA" << endl;
	}
}

void hay_clientes_en_espera(SistemaVentas& ventas) {
	string codigo_concierto;
	cin >> codigo_concierto;
	cout << "hay_clientes_en_espera " << codigo_concierto << " => ";
	try {
		if (ventas.hay_clientes_en_espera(codigo_concierto))
			cout << "SI" << endl;
		else
			cout << "NO" << endl;
	}
	catch (EConciertoInexistente) {
		cout << "CONCIERTO_INEXISTENTE" << endl;
	}
}

void proximo_cliente(SistemaVentas& ventas) {
	string codigo_concierto;
	cin >> codigo_concierto;
	cout << "proximo_cliente " << codigo_concierto << " => ";
	try {
		cout << ventas.proximo_cliente(codigo_concierto) << endl;
	}
	catch (EConciertoInexistente) {
		cout << "CONCIERTO_INEXISTENTE" << endl;
	}
	catch (EConciertoSinEsperas) {
		cout << "CONCIERTO_SIN_ESPERAS" << endl;
	}
}

void venta(SistemaVentas& ventas) {
	string codigo_concierto;
	cin >> codigo_concierto;
	cout << "venta " << codigo_concierto << " => ";
	try {
		ventas.venta(codigo_concierto);
		cout << "OK" << endl;
	}
	catch (EConciertoInexistente) {
		cout << "CONCIERTO_INEXISTENTE" << endl;
	}
	catch (EConciertoSinEsperas) {
		cout << "CONCIERTO_SIN_ESPERAS" << endl;
	}
}

void abandona(SistemaVentas& ventas) {
	string codigo_cliente;
	cin >> codigo_cliente;
	cout << "abandona " << codigo_cliente << " => ";
	try {
		ventas.abandona(codigo_cliente);
		cout << "OK" << endl;
	}
	catch (EClienteInexistente) {
		cout << "CLIENTE_NO_EXISTE" << endl;
	}

}

void clientes(SistemaVentas& ventas) {
	cout << "clientes => ";
	lista(ventas.clientes());
	cout << endl;
}

void num_clientes(SistemaVentas& ventas) {
	cout << "num_clientes => ";
	cout << ventas.num_clientes() << endl;
}

void num_conciertos(SistemaVentas& ventas) {
	cout << "num_conciertos => ";
	cout << ventas.num_conciertos() << endl;
}



int main() {
   SistemaVentas ventas;
   string comando;
   while(cin >> comando) {
       if (comando == "an_cliente") an_cliente(ventas);
	   else if (comando == "an_concierto") an_concierto(ventas);
	   else if (comando == "borra_cliente") borra_cliente(ventas);
	   else if (comando == "borra_concierto") borra_concierto(ventas);
	   else if (comando == "pon_en_espera") pon_en_espera(ventas);
	   else if (comando == "hay_clientes_en_espera") hay_clientes_en_espera(ventas);
	   else if (comando == "proximo_cliente") proximo_cliente(ventas);
	   else if (comando == "venta") venta(ventas);
	   else if (comando == "abandona") abandona(ventas);
	   else if (comando == "clientes") clientes(ventas);
	   else if (comando == "num_clientes") num_clientes(ventas);
	   else if (comando == "num_conciertos") num_conciertos(ventas);

	}
	return 0;
}

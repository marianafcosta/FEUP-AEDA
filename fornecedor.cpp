#include "fornecedor.h"

Fornecedor::Fornecedor () {};

Fornecedor::Fornecedor(string nome, unsigned int NIF, string morada) {
	this->nome=nome;
	this->NIF=NIF;
	this->morada=morada;
	lucro = 0;
}

void Fornecedor::setNome(string nome) {
	this->nome=nome;
}

void Fornecedor::setNIF(unsigned int NIF) {
	this->NIF=NIF;
}

void Fornecedor::setMorada(string morada) {
	this->morada=morada;
}

string Fornecedor::getNome() const {
	return nome;
}

unsigned int Fornecedor::getNIF() const {
	return NIF;
}

string Fornecedor::getMorada() const {
	return morada;
}

vector<Oferta> Fornecedor::getOfertas() const {
	return ofertas;
}


int Fornecedor::addOferta(Data data, string destino, string barco, unsigned int lotacaoMax) {
	Oferta * o1 = new Oferta(barco, lotacaoMax, destino, data);

	for (unsigned int i= 0; i < ofertas.size(); i++) {
		if (ofertas[i] == *o1)
			return 1;
	}
	ofertas.push_back(*o1);
	return 0;
}



int Fornecedor::removeOferta(Data data, string destino, string barco, unsigned int lotacaoMax) {
	Oferta o1(barco, lotacaoMax, destino, data);

	for(unsigned int i = 0 ; i < ofertas.size(); i++) {
		if (ofertas[i] == o1) {
			ofertas.erase(ofertas.begin()+i);
			return 0;
		}
	}
	return 1;
}


void Fornecedor::printOfertas(std::ostream &os) const {

	os << "**** " << nome << " ****" << endl;

	for (unsigned int i = 0; i < ofertas.size(); i++) {

		os << "Oferta " << i << ":"  << endl
				<< "Barco: " << ofertas.at(i).getBarco() << endl
				<< "Lotacao maxima: " << ofertas.at(i).getLotacaoMax() << endl
				<< "Destino: " << ofertas.at(i).getDestino() << endl
				<< "Data: " << ofertas.at(i).getData().printData() << endl
				<< "Lotacao atual: " << ofertas.at(i).getLotacao() << endl << endl;
	}
}

void Fornecedor::printInfo() const {

	cout << "Fornecedor: " << nome << endl
			<< "NIF: " << NIF << endl
			<< "Morada: " << morada << endl
			<< "Lucro: " << lucro << endl
			<< "Preco por kilometro: " << precoKm << endl
			<< "Preco por escalao de lotacao maxima:" << endl
			<< " - 20 pessoas: " << precoLot.at(0) << endl
			<< " - 35 pessoas: " << precoLot.at(1) << endl
			<< " - 50 pessoas: " << precoLot.at(2) << endl << endl;
}

int Fornecedor::calculaLucro() {

	int sum=0;
	unsigned int lotacaoType;

	for(unsigned int i=0; i < ofertas.size(); i++) {

		lotacaoType == ofertas.at(i).getLotacaoMax();

		switch(lotacaoType){

		case 20:
			sum += precoLot.at(0) * ofertas.at(i).getLotacao() + precoKm * ofertas.at(i).getDistancia();
			break;
		case 35:
			sum += precoLot.at(1) * ofertas.at(i).getLotacao() + precoKm * ofertas.at(i).getDistancia();
			break;
		case 50:
			sum += precoLot.at(2) * ofertas.at(i).getLotacao() + precoKm * ofertas.at(i).getDistancia();
			break;
		}
	}

	lucro = sum;
	return sum;

}

void Fornecedor::printLucro() const {

	cout << "**** " << nome << " ****" << endl << "Lucro: " << getLucro() << endl;

}

void Fornecedor::updateOferta(const Oferta &o1) {

	for (unsigned int i = 0; i < ofertas.size(); i++) {

		if (ofertas.at(i) == o1) {
			ofertas.at(i).addToLotacao();
			calculaLucro();
		}

	}

}

void Fornecedor::removeOfertaMenu(unsigned int i) {

	if ((i-1) >= 0 && (i-1) < ofertas.size()) {
		ofertas.erase(ofertas.begin()+i);
	}
	else
		// throw OfertaInexistente
		;

}

ostream & operator <<(ostream &os, const Fornecedor &fornecedor) {

	fornecedor.printOfertas(os);
	return os;
}


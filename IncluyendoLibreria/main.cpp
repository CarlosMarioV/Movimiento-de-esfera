#include<iostream>
#include<string>
#include<sstream>
#include<math.h>

using namespace std;

class Pais{

private:
	string nombreP;
	float bienestarDeLosHabitantes;
	float esperanzaDeVida;
	float inequidadSocial;
	float huellaEcologica;
	float a;
	float b;
	float c;
	float d;

public:
	Pais()
	{
		nombreP="";
		bienestarDeLosHabitantes=0;
		esperanzaDeVida=0;
		inequidadSocial=0.0;
		huellaEcologica=0.0;
		a=0.452;
		b=0.158;
		c=3.951;
		d=2.067;

	}

	Pais(string PS, float BE, float EV, float IS, float HE)
	{
		nombreP=PS;
		bienestarDeLosHabitantes=BE;
		esperanzaDeVida=EV;
		inequidadSocial=IS;
		huellaEcologica=HE;
		a=0.452;
		b=0.158;
		c=3.951;
		d=2.067;

	}
	void setNombreP(string nombreP){
		this->nombreP=nombreP;
	}

	void setBienestarDeLosHabitantes(float bienestarDeLosHabitantes){
		this->bienestarDeLosHabitantes=bienestarDeLosHabitantes;
	}
	void setEsperanzaDeVida(float esperanzaDeVida){
		this->esperanzaDeVida=esperanzaDeVida;
	}
	void setInequidadSocial(float inequidadSocial){
		this->inequidadSocial=inequidadSocial;
	}
	void setHuellaEcologica(float huellaEcologica){
		this->huellaEcologica=huellaEcologica;
	}
	string getNombreP(){
		return nombreP;
	}
	int getBienestarDeLosHabitantes(){
		return bienestarDeLosHabitantes;
	}
	int getEsperanzaDeVida(){
		return esperanzaDeVida;
	}
	float getInequidadSocial(){
		return inequidadSocial;
	}
	float getHuellaEcologica(){
		return huellaEcologica;
	}

	~Pais(){

	}
	//semaforos

	string colorBE(){
		if (bienestarDeLosHabitantes>=6)
			return "Verde";
		else
			if (bienestarDeLosHabitantes>=5&&bienestarDeLosHabitantes<6)
			return "Amarillo";
			else
				(bienestarDeLosHabitantes<5);
		return "Rojo";

	}
	string colorEV(){
		if (esperanzaDeVida>=75)
			return "Verde";
		else
			if (esperanzaDeVida>=65&&esperanzaDeVida<75)
			return "Amarillo";
			else
				(esperanzaDeVida<65);
		return "Rojo";
	}
	string colorIs(){
		if (inequidadSocial<0.15)
			return "Verde";
		else
			if (inequidadSocial>=0.15&&inequidadSocial<0.30)
			return "Amarillo";
			else
				(inequidadSocial>=0.30);
		return "Rojo";
	}
	string colorHE(){
		if (huellaEcologica<=1.73)
			return "Verde";
		else
			if (huellaEcologica>1.73&&huellaEcologica<3.46)
			return "Amarillo";
			else
				(huellaEcologica>=3.46);
		return "Rojo";
	}


//metodo iguales improvisado

	bool iguales(){
		if (colorBE()==colorEV()&&colorBE()==colorIs()&&colorBE()==colorHE())
			return true;
		else
			return false;

	}
	float P1(){
		return ((bienestarDeLosHabitantes-b)*esperanzaDeVida)+c;
	}
	float P2(){
		return (huellaEcologica+d);
	}
	//HPI
	float HPI(){
		return((a*(P1()/P2()))*(1-inequidadSocial));


	}
	//numbanda
	char numBanda(){
		if (HPI()>44.6){
			return '1';
		}
		else if ( HPI() >= 40.7 && HPI() <= 44.6){
			return '2';
		}
		else if ( HPI() >= 36.7 && HPI() <= 40.6){
			return '3';
		}
		else if ( HPI() >= 32.7 && HPI() <= 36.6){
			return '4';
		}
		else if ( HPI() >= 28.7 && HPI() <= 32.6){
			return '5';
		}
		else if ( HPI() >= 24.8 && HPI() <= 28.6){
			return '6';
		}
		else if ( HPI() >= 20.8 && HPI() <= 24.7){
			return '7';
		}
		else if ( HPI() >= 16.8 && HPI() <= 20.7){
			return '8';
		}
		else if ( HPI() < 16.8){
			return '9';
		}

	}
	string igualColor(){
		if(colorBE()==colorEV() && colorBE()==colorHE() && colorBE()==colorIs()){
		return "Todas las dimenciones de son del mismo color";
		}
		else {
			return "Las dimenciones no son del mismo color";
		}

	}

	//metodo toString
	string toString(){
		stringstream x;
		x<<"Los datos de "<<nombreP<<" son: "<<endl;
		x<<"Bienestar Experimentado:"<<bienestarDeLosHabitantes;
		x<<"  COLOR: "<<colorBE()<<endl;
		x<<"Esperanza de Vida:"<<esperanzaDeVida;
		x<<"  COLOR: "<<colorEV()<<endl;
		x<<"Inequidad Social:"<<inequidadSocial;
		x<<"  COLOR: "<<colorIs()<<endl;
		x<<"Huella Ecologica:"<<huellaEcologica;
		x<<"  COLOR: "<<colorHE()<<endl;
		x<<"El indice de felicidad planetaria es: "<<HPI()<<endl;
		x<<"y clasifica en el numero de banda: "<<numBanda()<<endl<<endl;
		x<<igualColor()<<endl;
			return x.str();

	}
};

void MayorHPI(Pais PAIS1,Pais PAIS2)
{
    if(PAIS1.HPI() > PAIS2.HPI())
    {
       cout<<"El pais con mayor HPI es: "<<PAIS1.getNombreP()<<endl;
    }
    else if(PAIS1.HPI() < PAIS2.HPI())
    {
       cout<<"El pais con mayor HPI es: "<<PAIS2.getNombreP()<<endl;
    }
    else
    {
       cout<<"Tienen el mismo indice"<<endl;
    }

}

int main(){


	string PS;
	float BE;
	float EV;
	float IS;
	float HE;
	cout<<"Digite el nombre del pais: ";
	cin>>PS;
	cout<<endl;
	cout<<"Digite el bienestar experimentado: ";
	cin>>BE;
	cout<<endl;
	cout<<"Digite la esperanza de vida: ";
	cin>>EV;
	cout<<endl;
	cout<<"Digite la inequidad social: ";
	cin>>IS;
	cout<<endl;
	cout<<"Digite la huella ecologica: ";
	cin>>HE;
	cout<<endl;
	Pais PAIS1(PS,BE,EV, IS,HE);
	cout<<PAIS1.toString()<<endl;

//////Creacion del obJeto 2

	Pais PAIS2;
	cout<<"Digite el nombre del pais: ";
	cin>>PS;
	cout<<endl;
	cout<<"Digite el bienestar experimentado: ";
	cin>>BE;
	cout<<endl;
	cout<<"Digite la esperanza de vida: ";
	cin>>EV;
	cout<<endl;
	cout<<"Digite la inequidad social: ";
	cin>>IS;
	cout<<endl;
	cout<<"Digite la huella ecologica: ";
	cin>>HE;
	cout<<endl;
	PAIS2.setNombreP(PS);
	PAIS2.setBienestarDeLosHabitantes(BE);
	PAIS2.setEsperanzaDeVida(EV);
	PAIS2.setInequidadSocial(IS);
	PAIS2.setHuellaEcologica(HE);
	cout<<PAIS2.toString()<<endl;

	MayorHPI(PAIS1,PAIS2);

}


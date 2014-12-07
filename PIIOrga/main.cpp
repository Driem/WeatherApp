#include <iostream>
#include "tinyxml2.h"
#include <iostream>
#include <list>
#include <windows.h>
#include <sstream>
#include <ctime>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace tinyxml2;
using namespace sf;

string TraductorN(string nube)
{
    if(nube == "overcast clouds")
        nube = "Nublado";
    if(nube =="broken clouds")
        nube = "Muy nuboso";

    return nube;
}

string TraductorV(string Viento)
{
    if(Viento == "Calm")
        Viento = "Calmado";
    if(Viento == "Light breeze")
        Viento = "brisa ligera";

    return Viento;
}


float getTemperatureEnCelcius(string nombre_archivo)
{
    float K, C;
    XMLDocument doc;
    doc.LoadFile(nombre_archivo.c_str());//Se abre el archivo XML
    XMLElement* current_element = doc.FirstChildElement("current")->FirstChildElement("temperature");// Se crea un elemento que apunta a current que es el elemento central o podemos decir que es la raiz
    //y este a su vez apunta al elemento temperatura
    K = atof(current_element->Attribute("value"));//Retorna el attributo value del tag temperature y lo transforma a flotante gracias al metodo atof
    C = K - 273.15;
    return C;

}

//Devuelve el attributo value del tag humidity
int getHumidity(string nombre_archivo)
{
    XMLDocument doc; // Se crea la variable para mandar a llamar elemento
    doc.LoadFile(nombre_archivo.c_str());//Se abre el archivo XML
    XMLElement* current_element = doc.FirstChildElement("current")->FirstChildElement("humidity");// Se crea un elemento que apunta a current que es el elemento central o podemos decir que es la raiz
    //y este a su vez apunta al elemento humidity
    return atoi(current_element->Attribute("value"));//Devuelve el attributo value del tag humidity y lo convierte a int gracias al metodo atoi
}

//Devuelve el attributo value del tag pressure
int getPressure(string nombre_archivo)
{
    XMLDocument doc; // Se crea la variable para mandar a llamar elemento
    doc.LoadFile(nombre_archivo.c_str());//Se abre el archivo XML
    XMLElement* current_element = doc.FirstChildElement("current")->FirstChildElement("pressure");// Se crea un elemento que apunta a current que es el elemento central o podemos decir que es la raiz
    //y este a su vez apunta al elemento pressure
    return atoi(current_element->Attribute("value")); //Devuelve el attributo value del tag pressure y lo convierte a int gracias al metodo atoi
}

//Devuelve el attributo value del tag speed dentro del tag wind
float getWindSpeed(string nombre_archivo)
{
    XMLDocument doc; // Se crea la variable para mandar a llamar elemento
    doc.LoadFile(nombre_archivo.c_str());//Se abre el archivo XML
    XMLElement* current_element = doc.FirstChildElement("current")->FirstChildElement("wind")->FirstChildElement("speed");// Se crea un elemento que apunta a current que es el elemento central o podemos decir que es la raiz
    //y este a su vez apunta al elemento wind que tambien apunta a speed (Me gusto ahorrarme codigo :D)
    return atof(current_element->Attribute("value"));//Devuelve el attributo value del tag speed dentro del tag wind
}

string getWindStas(string nombre_archivo)
{
    XMLDocument doc; // Se crea la variable para mandar a llamar elemento
    doc.LoadFile(nombre_archivo.c_str());//Se abre el archivo XML
    XMLElement* current_element = doc.FirstChildElement("current")->FirstChildElement("wind")->FirstChildElement("speed");// Se crea un elemento que apunta a current que es el elemento central o podemos decir que es la raiz
    //y este a su vez apunta al elemento wind que tambien apunta a speed (Me gusto ahorrarme codigo :D)
    return TraductorV(current_element->Attribute("name"));//Devuelve el attributo value del tag speed dentro del tag wind
}

//Devuelve el attributo name del tag city
string getCityName(string nombre_archivo)
{

    XMLDocument doc;// Se crea la variable para mandar a llamar elemento
    doc.LoadFile(nombre_archivo.c_str());//Se abre el archivo XML
    XMLElement* current_element = doc.FirstChildElement("current")->FirstChildElement("city");// Se crea un elemento que apunta a current que es el elemento central o podemos decir que es la raiz
    //y este a su vez apunta al elemento city
    return current_element->Attribute("name");//Devuelve el attributo name del tag city

}

/*string getContryName(string nombre_archivo)
{

    XMLDocument doc;// Se crea la variable para mandar a llamar elemento
    doc.LoadFile(nombre_archivo.c_str());//Se abre el archivo XML
    XMLElement* current_element = doc.FirstChildElement("current")->FirstChildElement("city")->FirstChildElement("Country");// Se crea un elemento que apunta a current que es el elemento central o podemos decir que es la raiz
                                                                                                    //y este a su vez apunta al elemento city
    return current_element->Attribute("Honduras");
}*/

string GetDireccion(string direct)
{
    stringstream ss;
    string Direccion;
    ss <<"bin\\wget.exe \"http://api.openweathermap.org/data/2.5/weather?q="<<direct<<"&mode=xml\"";
    Direccion = ss.str();
    return Direccion;
}

string GetArchivo(string direct)
{
    stringstream ss;
    string ciudad;
    ss<<"weather@q="<<direct<<"&mode=xml";
    ciudad = ss.str();
    return ciudad;
}


string GetTypeCloud(string NArch)
{
    XMLDocument doc;// Se crea la variable para mandar a llamar elemento
    doc.LoadFile(NArch.c_str());//Se abre el archivo XML
    XMLElement* current_element = doc.FirstChildElement("current")->FirstChildElement("clouds");// Se crea un elemento que apunta a current que es el elemento central o podemos decir que es la raiz
    //y este a su vez apunta al elemento city
    return TraductorN(current_element->Attribute("name"));


}

void Show(string direct)
{

    //ShellExecute(NULL, "open", "http://api.openweathermap.org/data/2.5/weather?q=SPS&mode=xml", NULL, NULL, SW_SHOWNORMAL);
    cout<<"Ciudad : "<<getCityName(GetArchivo(direct))<<endl;
    // cout<<"Pais : "<<getContryName(GetArchivo(direct))<<endl;
    cout<<"Estado del Viento: "<<getWindStas(GetArchivo(direct))<<endl;
    cout<<"Temperatura: "<<getTemperatureEnCelcius(GetArchivo(direct))<<" Celsius"<<endl;
    cout<<"Nubes: "<<GetTypeCloud(GetArchivo(direct))<<endl;
    //cout<<"Presion: "<<getPressure(GetArchivo(direct))<<endl;


}


int main()
{

    string Direccion,direct;
    cout<<"Ingrese Ciudad"<<endl;
    getline(cin,direct);
    Direccion = GetDireccion(direct);
    system(Direccion.c_str());
    Show(direct);

/*
    RenderWindow window(sf::VideoMode(800, 500), " Organizacion de Archivos: Clima ",Style::Titlebar | Style::Close);
     Texture Fondo;
     Fondo.loadFromFile("C:\\Users\\DELL-INSPIRON15R\\Desktop\\Universidad\\PIIOrga\\Recursos\\Nubes (7).png");
    Sprite Fondo1(Fondo);
    while (window.isOpen())
    {
        sf::Event event;

    while (window.isOpen())
    {


        sf::Event event;

        while (window.pollEvent(event))
        {


            if(event.type ==Event::Closed)
                window.close();


    if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }




        }


    window.clear();

       window.draw(Fondo1,RenderStates::Default);






        window.display();

    }

    }*/

    system("PAUSE");
    return 0;
}

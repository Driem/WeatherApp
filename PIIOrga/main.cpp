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
    ss <<"bin\\wget.exe -N -nv \"http://api.openweathermap.org/data/2.5/weather?q="<<direct<<"&mode=xml\"";
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
/* HWND hwnd_win = GetForegroundWindow();
    ShowWindow(hwnd_win,SW_HIDE);
    //Espera 4 segundos
    _sleep(4000);
    //vuelve a mostrar la consola.
    ShowWindow(hwnd_win,SW_SHOW);*/


    string Direccion,direct;
    //cout<<"Ingrese Ciudad"<<endl;
    //getline(cin,direct);
   direct = "Puerto cortes";
    Direccion = GetDireccion(direct);
    system(Direccion.c_str());
    Show(direct);
string T = static_cast<std::ostringstream*>(&(ostringstream() << getTemperatureEnCelcius(GetArchivo(direct))))->str();

    sf::Font font;
            if (!font.loadFromFile("GoodDog.otf"))
            return EXIT_FAILURE;
            sf::Text text(getCityName(GetArchivo(direct)), font, 30);
            sf::Text text1(getWindStas(GetArchivo(direct)), font, 30);
           sf::Text text2(T, font, 30);
            sf::Text text3(GetTypeCloud(GetArchivo(direct)), font, 30);
            text.setPosition(130,10);
            text1.setPosition(130,40);
            text2.setPosition(130,70);
            text3.setPosition(130,100);
            text.setColor(Color::Yellow);
            text1.setColor(Color::Yellow);
            text2.setColor(Color::Yellow);
            text3.setColor(Color::Yellow);

    Texture Fondo;
     Fondo.loadFromFile("Recursos\\descarga.jpg");
    Sprite Fondo1(Fondo);
    RenderWindow window(sf::VideoMode(341, 148), " Organizacion de Archivos: Clima ",Style::Titlebar | Style::Close);

    while (window.isOpen())
    {
        sf::Event event;

    while (window.isOpen())
    {


        sf::Event event;

        while (window.pollEvent(event))
        {


            if(event.type == Event::Closed){
                window.close();
                exit(0);

            }



    if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }




        }


    window.clear();

       window.draw(Fondo1,RenderStates::Default);
       window.draw(text);
       window.draw(text1);
       window.draw(text2);
       window.draw(text3);


        window.display();

    }

    }

    system("PAUSE");
    return 0;
}

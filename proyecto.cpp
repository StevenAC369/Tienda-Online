#include<iostream>
#include<string>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <cstdlib>
#include <conio.h>

using namespace std;

int opcion, productos_agregados=0;
string productos[15] = {"Resistencia", "Diodo led", "Transistor", "Condensador Electrolitico", "Mostfet", "Bateria de Lipo 4,2V 3A", "Cautin Lapiz Stanley 30W", "Protoboard Grande 830 puntos", "Bascula Digital 5Kg", "Contador Geiger digital GAMMA-SCOUT", "Tranformador de 120V a 12V 300W", "Arduino Uno R3 Original Italiano", "Kit de soldadura basico; St, pasta y pistola para soldar de 45W", "Termometro Infrarrojo", "Parlante Nakamichi 200W 6.5 pulgadas"};
double cantidad_de_productos[15] ;
double precio[15] = {0.05, 0.030, 1.00, 1.00, 1.40, 10.50, 5.00, 4.50, 14.50, 46.70, 15.00, 27.00, 35.00, 7.00, 18.00};
double total_a_pagar = 0;
int n_factura=0;


// Colores 
const string RESET   = "\033[0m";
const string RED     = "\033[31m";
const string GREEN   = "\033[32m";
const string YELLOW  = "\033[33m";
const string BLUE    = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN    = "\033[36m";
const string WHITE   = "\033[37m";
const string BOLD    = "\033[1m";

// Porcentaje de descuento
double& porcentaje_descuento() {
    static double valor = 0.0;
    return valor;
} 

void valor_asignado(double m) {
    porcentaje_descuento() = m * 10;
}



void buscar_agregar(int seleccion) {
    for(int a=0;a<15;a++) { 
        if (a + 1 == seleccion) {
            cout<<"Ingrese la cantidad de productos : ";
            int cantidad = 0; 
            cin>>cantidad;
            while (cin.fail() || cantidad < 1 || cantidad >1000) { 
            cin.clear(); 
            cin.ignore(1000, '\n'); 
            cout <<RED+"Cantidad erronea. Intente nuevamente: "+RESET;
            cantidad=0;
            cin >> cantidad;
            }
            cantidad_de_productos[a] += cantidad;
            cout<<RESET<<"----------------------------------------------------------------"<<endl;
            cout<<CYAN<<productos[a]<<GREEN<<" agregado al carro."<<endl;
            cout<<RESET<<"----------------------------------------------------------------"<<endl;
            cout<<"Presione cualquier tecla para continuar";
            getch();
            system("cls");
        }    
    } 
}

float calcular_precio(float n_productos, double precio) {
    double total = n_productos * precio;
    double descuento = 0;
    if (n_productos >= 1 && n_productos <=4 ) {
        descuento = 0;
        float valor_descuento = 0;
        valor_asignado(valor_descuento);
    } else if (n_productos >= 5 && n_productos <=10) {
        float valor_descuento = 0.10;
        descuento = total * valor_descuento;
        valor_asignado(valor_descuento);
    } else if (n_productos >=11) {
        float valor_descuento = 0.15;
        descuento = total * valor_descuento;
        valor_asignado(valor_descuento);
    } else {
        cout<<"Verificar si los valores son correctos";
        return 0;
    }
    total -= descuento;
    return total;
}
string quitar_espacios(const string& str) {
    string resultado;
    for (char c : str) {
        if (c != ' ') resultado += c;
    }
    return resultado;
}

string limpiarTexto(const string& texto) {
    string limpio = texto;
    if (!limpio.empty() && limpio.front() == '"' or "'") limpio.erase(0, 1);  
    if (!limpio.empty() && limpio.back() == '"' or "'") limpio.erase(limpio.size() - 1);  
    return limpio;
}



int obtener_n_factura() {
    string factura_id_str;
    ifstream archivoLectura("Proyecto\\historial_local.py");
    if (archivoLectura.is_open()) {
        string linea;
        int numeros_de_facturas[100];
        int h=0;
        int mayor=0;
        int factura_id=0;
        while (getline(archivoLectura, linea)) {
            string limpia = quitar_espacios(linea);
            if (limpia.find("factura_id=") == 0) {
                factura_id_str = limpia.substr(limpia.find("=") + 1); 
                factura_id = stoi(factura_id_str);
                numeros_de_facturas[h] = factura_id;
                if (numeros_de_facturas[h] > mayor) {
                    mayor = numeros_de_facturas[h];
                }
                h++;
            }
        }

        archivoLectura.close();
        return mayor;
    } else {
        cout << "Error al abrir el archivo para registrar el historial." << endl;
    }
}

string obtener_datos_de_config(const string& clave) {
    ifstream file("config.py");
    if (!file.is_open()) {
        cout << "Error al abrir el archivo de configuración. Verifique el codigo y vuelva a compilar" << endl;
        return 0;
    }
    string linea;
    while (getline(file, linea)) {
        size_t pos = linea.find(clave + " = ");
        if (pos != string::npos) {
            string valor = linea.substr(pos + clave.length() + 3); 
            file.close();
            valor = limpiarTexto(valor);
            return valor;
        }
    }
}


facturar(string cedula, string nombres, string direccion, string celular) {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream fechaStream, horaStream;

    fechaStream << std::put_time(&tm, "%d-%m-%Y");
    horaStream << std::put_time(&tm, "%H:%M:%S");

    std::string fecha = fechaStream.str();
    std::string hora = horaStream.str();

    int contador1 = 0;
    cout<<MAGENTA<<"Fecha: "<<fecha<<endl;
    cout<<MAGENTA<<"Hora: "<<hora<<endl;
    cout<<MAGENTA<<"Cedula/RUC: "<<GREEN<<cedula<<endl;
    cout<<MAGENTA<<"Nombre: "<<GREEN<<nombres<<endl;
    cout<<MAGENTA<<"Direccion: "<<GREEN<<direccion<<endl;
    cout<<MAGENTA<<"Celular: "<<GREEN<<celular<<endl;
    int n_factura = obtener_n_factura();

   
    ofstream historial("historial.txt", ios::app);
    if (historial.is_open()) {
        historial<<"______________________________________________________________________________________"<<endl;
        historial<<"Factura N°: "<<n_factura<<endl;
        historial<<"Fecha: "<<fecha<<endl;
        historial<<"Hora: "<< hora<<endl;
        historial<<"Factura Nº "<<endl;
        historial<<"Cedula/RUC: "<<cedula<<endl;
        historial<<"Direccion: "<<direccion<<endl;
        historial<<"..................................... DESCRIPCION ..................................."<<endl;
        for(int a=0;a<15;a++)  {
            if (cantidad_de_productos[a] > 0) {
                double cantidad=0;
                double precio_=0;
                double total=0;
                cantidad = cantidad_de_productos[a];
                precio_ = precio[a];
                historial << fixed << setprecision(2);
                total =  calcular_precio(cantidad, precio_);
                historial << "Producto: " << productos[a] << " - Cantidad: " << cantidad_de_productos[a] <<" - Decuento Unitario: "<< porcentaje_descuento() <<" - Precio Unitario: " <<precio[a]<<" Total: "<< total << endl;
                total_a_pagar = total_a_pagar + total;
            } 
            if (cantidad_de_productos[a] == 0) {
                contador1++;
            } 
        }
        if (contador1 == 15) {
            cout<<RED<<"La cesta esta vacia! Agrege productos para continuar!"<<RESET;
        }
        historial<<"......................................................................................"<<endl;
        // proceso para sacar subtotal
        double subtotal = 0;
        ostringstream stream;
        stream << fixed << setprecision(2) << total_a_pagar;
        subtotal = total_a_pagar*0.85;
        historial<<"Subtotal: "<<subtotal<<endl;
        // proceso para sacar iva
        double iva = 0;
        historial<<"Iva (15%): "<<total_a_pagar*0.15<<endl;
        // proceso para sacar total 
        historial<<"Total: $"<<total_a_pagar<<endl;
        historial<<"______________________________________________________________________________________"<<endl;
        historial.close();
        string total_a_pagar_str = to_string(total_a_pagar);
        string comando = "python Proyecto\\proyecto.py " + cedula + " \"" + nombres + "\" \"" + direccion + "\" " + celular + " " + fecha + " " + hora + " " + total_a_pagar_str;
        system(comando.c_str());
        fstream archivo("Proyecto\\historial_local.py", ios::app);  
        if (archivo.is_open()) {
            // archivo <<"print('"<<CYAN<<"---------------------------------------------------------------------------')"<<endl;
            archivo <<"\nprint('''"<<BLUE<<"Fecha:  "<<MAGENTA<<fecha<<endl;
            archivo <<BLUE<<"Hora: "<<MAGENTA<<hora<<endl;
            archivo <<BLUE<<"Cedula: "<<MAGENTA<<cedula<<endl;
            archivo <<BLUE<<"Nombre: "<<MAGENTA<<nombres<<endl;
            archivo <<BLUE<<"Direccion: "<<MAGENTA<<direccion<<endl;
            archivo <<BLUE<<"Celular: "<<MAGENTA<<celular<<endl;
            archivo <<BLUE<<"Total de compra realizada: "<<MAGENTA<<total_a_pagar<<endl;
            archivo <<RESET<<"''')"<<endl;
            archivo.close();
            cout << "Datos guardados localmente." << endl;
        } else {
            cout << "Error al abrir el archivo." << endl;
        }
        string precioStr = to_string(total_a_pagar);
        string correo = obtener_datos_de_config("CORREO_PAYPAL");
        string producto = obtener_datos_de_config("ITEM_NAME");
        string url = "https://www.paypal.com/cgi-bin/webscr?cmd=_xclick&business=" + correo + "&item_name=" + producto + "&amount=" + precioStr + "&currency_code=USD";
        system(("start \"\" \"" + url + "\"").c_str());
        cout<<CYAN<<"Presione cualquier tecla para continuar";
        getch();
        system("cls");
        for (int x=0;x<15;x++) {
            cantidad_de_productos[x] = 0;
        }
        total_a_pagar = 0;
        iva = 0;
        subtotal = 0;
    // } else {
    //  cout<<RED<<"No se pudo registrar la informacion correspondiente!"<<RESET;
    }
}

int main() {
    do {
        cout<<CYAN<<R"(
           |
    o------| |------o   ____________________________________
           | |         |   Tienda de Electronica by Steven  |         |\
                                                                o-----| >-----o
                                                                      |/)"<<endl;
        cout<<BLUE<<"----------------------------------------------------------------------------"<<endl<<RESET<<"Seleccione una opcion para continuar."<<endl<<CYAN<<"----------------------------------------------------------------------------"<<endl<<YELLOW<<"1. "<<MAGENTA<<"Realizar predidos de productos. \n"<<CYAN<<"----------------------------------------------------------------------------"<<endl<<YELLOW<<"2. "<<MAGENTA<<"Verificar precios de productos. \n"<<YELLOW<<CYAN<<"----------------------------------------------------------------------------"<<endl<<YELLOW<<"3. "<<MAGENTA<<"Generar factura.\n"<<CYAN<<"----------------------------------------------------------------------------"<<endl<<YELLOW<<"4. "<<MAGENTA<<"Eliminar o limpiar cesta. \n"<<YELLOW<<CYAN<<"----------------------------------------------------------------------------"<<endl<<YELLOW<<"5. "<<MAGENTA<<"Crear base de datos para historial (por primera vez)"<<CYAN<<endl<<"----------------------------------------------------------------------------"<<endl<<YELLOW<<"6. "<<MAGENTA<<"Ver historial"<<endl<<CYAN<<"----------------------------------------------------------------------------"<<endl<<YELLOW<<"7. "<<MAGENTA<<"Salir"<<endl<<CYAN<<"----------------------------------------------------------------------------"<<endl;;
        cout<<"Opcion: "<<RESET;
        cin>>opcion;
        cout<<RESET;
        while (cin.fail() || opcion < 1 || opcion > 7) { 
            cin.clear(); 
            cin.ignore(1000, '\n'); 
            cout <<RED+"Opción invalida. Intente nuevamente: "+RESET;
            cin >> opcion;
        }

        switch (opcion)
        {
        case 1:
            cout<<MAGENTA<<"Seleccione un producto del catalogo (Cantidad Limite de 1000 por articulo): \n";
            for (int x=0; x<15; x++) {
                cout<<YELLOW<<x+1<<". "<<GREEN<<productos[x]<<CYAN<<" - USD = $ "<<precio[x]<<endl;
                cout<<BLUE<<"----------------------------------------------------------------------------"<<endl;
            }
            cout<<YELLOW<<"16. "<<RED<<"Volver"<<endl;
            cout<<BLUE<<"----------------------------------------------------------------------------"<<endl;
            cout<<CYAN<<"Opcion: "<<RESET;
            int seleccion;
            cin>>seleccion;
            while (cin.fail() || seleccion < 1 || seleccion > 16) {
                cin.clear(); 
                cin.ignore(1000, '\n'); 
                cout <<RED+"Opción invalida. Intente nuevamente: "+RESET;
                
                cin >> seleccion;
            }
            if (seleccion == 16) {
                system("cls");
                break;
            } 
            buscar_agregar(seleccion);
            break;
        case 2: {
            int contador_productos = 0; 
            for(int a=0;a<15;a++)  {
                if (cantidad_de_productos[a] == 0) {
                    contador_productos = contador_productos + 1;
                }
            }
            if (contador_productos == 15) {
                system("cls");
                cout<<RED<<"La cesta esta vacia, agrege productos para continuar!"<<RESET<<endl;
                break;
            } else { 
            for(int a=0;a<15;a++)  {
                if (cantidad_de_productos[a] > 0) {
                    double cantidad=0;
                    double precio_=0;
                    double total=0;
                    cantidad = cantidad_de_productos[a];
                    precio_ = precio[a];
                    cout << fixed << setprecision(2);
                    total =  calcular_precio(cantidad, precio_);
                    cout <<GREEN<< "Producto: " <<YELLOW<< productos[a] <<RESET<< " - "<<GREEN<<"Cantidad: " <<YELLOW<< cantidad_de_productos[a] <<RESET<<" - "<<GREEN<<"Decuento: $ "<<BLUE<< porcentaje_descuento() <<RESET<<" - "<<GREEN<<"Precio Unitario: $ " <<BLUE<<precio[a] <<RESET<<" -"<<GREEN<<" Total: $ "<<BLUE<< total << endl;
                    cout<<BLUE<<"----------------------------------------------------------------------------"<<endl;
                    total_a_pagar = total_a_pagar + total;
                    }
            }
            // proceso para sacar subtotal
            double subtotal = 0;
            subtotal = total_a_pagar*0.85;
            cout<<GREEN<<"Subtotal: $ "<<YELLOW<<subtotal<<endl;
            cout<<CYAN<<"----------------------------------------------------------------------------"<<endl;
            // proceso para sacar iva
            double iva = 0;
            cout<<GREEN<<"Iva (15%): $"<<YELLOW<<total_a_pagar*0.15<<endl;
            cout<<CYAN<<"----------------------------------------------------------------------------"<<endl;
            // proceso para sacar total ×
            cout<<GREEN<<"Total a pagar: $"<<YELLOW<<total_a_pagar<<endl;
            cout<<CYAN<<"----------------------------------------------------------------------------"<<endl;
            cout<<RESET<<"Presione cualquier tecla para continuar";
            getch();
            system("cls");
            total_a_pagar = 0;
            break;
            }
            }
        case 3: {
            int contador_productos = 0; 
            for(int a=0;a<15;a++)  {
                if (cantidad_de_productos[a] == 0) {
                    contador_productos = contador_productos + 1;
                }
            }
            if (contador_productos == 15) {
                system("cls");
                cout<<RED<<"La cesta esta vacia, agrege productos para continuar!"<<RESET<<endl;
                break;
            } else { 
            cout<<MAGENTA<<"Seleccione el tipo de dato para generar la factura."<<YELLOW<<"\n1. "<<GREEN<<"Consumidor Final\n"<<YELLOW<<"2. "<<GREEN<<"Con datos\n"<<YELLOW<<"3. "<<GREEN<<"Volver";
            cin>>seleccion;
            while (cin.fail() || seleccion < 1 || seleccion > 3) { 
                cin.clear();
                cin.ignore(1000, '\n'); 
                cout << RED<<"Opción invalida. Intente nuevamente: "<<RESET;
                cin >> seleccion;
                }
                switch (seleccion)
                {
                case 1: {
                    facturar("999999999", "consumidor final", "9999999999", "999999999999");
                    break;
                }
                case 2: {
                    string documento_id; 
                    string nombres;
                    string direccion;
                    string celular; 
                    cout<<MAGENTA<<"Ingrese el número de Documento: "<<RESET;
                    cin>>documento_id;
                    cout<<MAGENTA<<"Ingrese el nombre: "<<RESET;
                    cin>>nombres;
                    cout<<MAGENTA<<"Ingrese la direccion: "<<RESET;
                    cin>>direccion;
                    cout<<MAGENTA<<"Ingrese el numero de celular: "<<RESET;
                    cin>>celular;
                    facturar(documento_id, nombres, direccion, celular);
                    }
                    break;
                case 3: break;
                }    
            }    
        }
        break;
        case 4: {
            int contador_productos = 0; 
            for(int a=0;a<15;a++)  {
                if (cantidad_de_productos[a] == 0) {
                    contador_productos = contador_productos + 1;
                }
            }
            if (contador_productos == 15) {
                system("cls");
                cout<<RED<<"La cesta esta vacia, agrege productos para continuar!"<<RESET<<endl;
                break;
            } else {
                char op;
                cout<<GREEN<<"a. "<<YELLOW<<"Eliminar un producto de la cesta. "<<endl;
                cout<<GREEN<<"b. "<<YELLOW<<"Limpiar cesta. "<<endl;
                cout<<GREEN<<"c. "<<YELLOW<<"Volver. "<<endl;
                cout<<CYAN<<"Seleccione una opcion para continuar: ";cin>>op;
                switch (op )
                    {
                    case 'a': {
                        for(int a=0;a<15;a++)  {
                            if (cantidad_de_productos[a] > 0) {
                                double cantidad=0;
                                double precio_=0;
                                double total=0;
                                cantidad = cantidad_de_productos[a];
                                precio_ = precio[a];
                                cout << fixed << setprecision(2);
                                total =  calcular_precio(cantidad, precio_);
                                cout <<GREEN<< a+1<<". " <<YELLOW<< productos[a] <<RESET<< " - "<<GREEN<<"Cantidad: " <<YELLOW<< cantidad_de_productos[a] <<RESET<<" - "<<GREEN<<"Decuento: $ "<<BLUE<< porcentaje_descuento() <<RESET<<" - "<<GREEN<<"Precio Unitario: $ " <<BLUE<<precio[a] <<RESET<<" -"<<GREEN<<" Total: "<<BLUE<< total << endl;
                                }
                            }
                            cout<<CYAN<<"Seleccione un producto de la lista a eliminar: "<<YELLOW;
                            int seleccion2=0;
                            cin.ignore();
                            cin>>seleccion2;
                            seleccion2 = seleccion2 - 1;
                            for (int a=0; a<15;a++) {
                                if (a == seleccion2) {
                                    cout<<RESET<<"Producto: "<<GREEN<<productos[a]<<RESET<<"Cantidad: "<<GREEN<<cantidad_de_productos[a]<<endl;
                                    cout<<"Seleccione la cantidad a eliminar; ";
                                    int cantidad_a_eliminar=0;
                                    cin>>cantidad_a_eliminar; 
                                    int cantidad_anterior=0;
                                    if (cantidad_a_eliminar > cantidad_de_productos[a]) {
                                        do {
                                        cout<<RED<<"La cantidad de productos a eliminar no puede ser mayor a la añadida!\n"<<MAGENTA<<"Ingrese Nuevamente la cantidad de productos a eliminar (0 para volver): ";
                                        cin>>cantidad_a_eliminar;
                                        } while (cantidad_a_eliminar > cantidad_de_productos[a]);
                                    } else if (cantidad_a_eliminar == 0) {
                                        cout<<RED<<"Cancelado!"<<RESET;
                                        break;
                                    } else if (cantidad_a_eliminar >= 1 && cantidad_a_eliminar <= cantidad_de_productos[a]) {
                                        cantidad_anterior = cantidad_de_productos[a];
                                        cantidad_de_productos[a] = cantidad_de_productos[a] - cantidad_a_eliminar;
                                    }
                                    if (cantidad_de_productos[a] == 0) {
                                    cout<<GREEN<<"Se ha eliminado todos "<<YELLOW<<"("<<cantidad_a_eliminar<<") "<<RESET<<"x "<<CYAN<<productos[a]<<MAGENTA<<" de la cesta!";
                                    break; 
                                    } else {
                                        cout<<GREEN<<"Se ha elimiando "<<YELLOW<<"("<<cantidad_a_eliminar<<")"<<RESET<<" x "<<CYAN<<productos[a]<<" de la cesta!"<<endl;
                                        cout<<CYAN<<"Cantidad anterior: "<<YELLOW<<cantidad_anterior<<endl;
                                        cout<<CYAN<<"Cantidad actual: "<<YELLOW<<cantidad_de_productos[a]<<endl;
                                        cout<<RESET<<"---------------------------------------------------------------"<<endl;
                                        cout<<CYAN<<"Presione cualquier tecla para continuar";
                                        getch();
                                        system("cls");
                                        break;
                                    }
                                }
                            }
                        }
                        break;
                    case 'b': 
                    {
                        for (int x=0;x<15;x++) {
                        cantidad_de_productos[x] = 0;
                        }
                        total_a_pagar = 0;
                        system("cls");
                        cout<<GREEN<<"Cesta limpiada sastifactoriamente!"<<RESET;
                        break;
                    }
                    case 'c': 
                    {
                        cout<<RED<<"Volviendo!"<<RESET;
                        system("cls");
                        break;
                    }
                    default: 
                    {
                        cout<<"Opcion no valida!"<<RESET;
                        break;
                    }
                }
            }
            break;
        }
        case 5: 
        {
        cout<<GREEN;
        system("python Proyecto\\create-database.py");
        break;
        }
        case 6:
        {
            system("python Proyecto\\historial_local.py");
            break;
        }
        case 7:
        {
            cout<<GREEN<<"Saliendo..."<<RESET;    
            break;
        }
        default: 
        {
            cout<<RED<<"Esta opción no es válida!";
            break;
        }
        
        } 
    } while (opcion!=7);
}

/*
ENTREGA 1 PROYECTO ESTRUCTURAS DE DATOS
PROFESOR ALEJANDRO CASTRO MARTINEZ
CLASE 2 A 4 PM

ESTUDIANTES
NICOLAS PERDIGON
LUIS ENRIQUE SANTOS
AMELIE GUERRERO JARAMILLO
*/



#include <iostream>
#include <vector>
#include "sistema.h"

int main(){
    Sistema sistema;
    std::string comando;
    std::cout<<"Proyecto de Estructuras de Datos"<<std::endl
    <<"Escriba 'ayuda' para ver una lista de posibles comandos."<<std::endl
    <<"Escriba 'salir' para salir."<<std::endl
    <<"Ingrese un comando:"<<std::endl;
    while (comando!="salir")
    {
        std::cout<<"$ ";
        getline(std::cin, comando);
        std::cout<<"Comando ingresado :"<<comando<<":"<<std::endl;
    
        if(comando.find("cargar_imagen")!=std::string::npos && comando.find("cargar_imagen")==0){
            if(comando[13]!=' '){
                std::cout<<"La imagen no ha podido ser cargada. Argumento esperado [cargar_imagen <nombre_imagen.pgm>]."<<std::endl;
            }
            else{
                comando.erase(0, 13+1);
                if(comando.size()==0){
                    std::cout<<"La imagen nombre_imagen.pgm no ha podido ser cargada. Falta argumento 1"<<std::endl;
                }
                else{
                    std::cout<<"La imagen :"<<comando<<": ha sido cargada."<<std::endl;
                    sistema.cargar_imagen(comando);
                }
            } 
        } else if(comando.find("cargar_volumen")!=std::string::npos && comando.find("cargar_volumen")==0){
            if(comando[14]!=' '){
                std::cout<<"El volumen no ha podido ser cargado. Argumento esperado [cargar_volumen <nombre_base> <n_im>]"<<std::endl;
            }
            else{
                comando.erase(0, 15);
                if(comando.size()==0){
                    std::cout<<"El volumen nombre_base no ha podido ser cargado. Falta argumento 1"<<std::endl;
                }
                else{
                    std::string arg1 = comando.substr(0, comando.find(' '));
                    comando.erase(0, arg1.size()+1);
                    if(comando.size()==0){
                        std::cout<<"El volumen '"<<arg1<< "' no ha podido ser cargado. Falta argumento 2"<<std::endl;
                    }
                    else{
                        comando.erase(0, (comando.find(' ')+1)); //queda un ' ' al inicio, entonces lo borramos
                        std::cout<<"El volumenha sido cargado."<<std::endl;
                        std::cout<<"nombre_base:"<<arg1<<":"<<std::endl;
                        std::cout<<"n_im:"<<comando<<":"<<std::endl; //el argumento 2 queda almacenado en comando
                        sistema.cargar_volumen(arg1, std::stoi(comando));
                    }
                    
                }
            }
        } else if(comando.find("info_volumen")!=std::string::npos && comando.find("info_volumen")==0){
            std::cout<<"Volumen cargado en memoria: nombre_base , tamaño: n_im , ancho: W , alto: H  "<<std::endl;
        } else if(comando.find("info_imagen")!=std::string::npos && comando.find("info_imagen")==0){
            sistema.info_imagen();
        } else if(comando.find("proyeccion2D")!=std::string::npos && comando.find("proyeccion2D")==0){
            if(comando[12]!= ' '){
                std::cout<<"La proyección 2D del volumen en memoria no ha podido ser generada. Argumento esperado [proyeccion2D <dirección> <criterio> <nombre_archivo.pgm>]"<<std::endl;
            }
            else{
                comando.erase(0, 13);
                if(comando.size()==0){
                    std::cout<<"La proyección 2D del volumen en memoria no ha podido ser generada. Falta argumento 1"<<std::endl;
                }
                else{
                    std::string direccion = comando.substr(0, comando.find(' '));
                    comando.erase(0, direccion.size()+1);
                    if(comando.size()==0){
                        std::cout<<"La proyección 2D del volumen en memoria no ha podido ser generada. Falta argumento 2"<<std::endl;
                    }
                    else{
                        std::string criterio = comando.substr(0, comando.find(' '));
                        comando.erase(0, criterio.size()+1);
                        if(comando.size()==0){
                            std::cout<<"La proyección 2D del volumen en memoria no ha podido ser generada. Falta argumento 3"<<std::endl;
                        }
                        else{
                            std::cout<<"La proyección 2D del volumen en memoria ha sido generada."<<std::endl;
                            std::cout<<"direccion :"<<direccion<<":"<<std::endl
                            <<"criterio :"<<criterio<<":"<<std::endl
                            <<"archivo :"<<comando<<":"<<std::endl;
                        }
                    }

                }
            }
        }else if(comando.find("segmentar")!=std::string::npos && comando.find("segmentar")==0){
            if(comando.find(' ')==std::string::npos){
                std::cout << "Error: Argumento esperado [segmentar <nombre_archivo.pgm> <segmentos>]" << std::endl;
            }else{
                comando.erase(0, 10);
                if(comando.size()==0){
                    std::cout<<"La imagen en memoria no pudo ser segmentada. Falta el nombre de archivo."<< std::endl;
                }
                else{
                    std::string nombreArchivo = comando.substr(0, comando.find(' '));
                    comando.erase(0, nombreArchivo.size()+1);
                    if(comando.size()==0){
                        std::cout<<"La imagen en memoria no pudo ser segmentada. Faltan segmentos."<< std::endl;
                    }
                    else{
                        std::vector<std::string> segmentos;
                        int i =0;
                        while (comando.find(' ') != std::string::npos) {
                            segmentos.push_back(comando.substr(0, comando.find(' ')));
                            comando.erase(0, comando.find(' ') + 1);
                        }
                        if (!comando.empty()) {
                            segmentos.push_back(comando);
                        }
                        std::cout<<"Nombre archivo '"<<nombreArchivo<<"'"<<std::endl<<"Segmentos:"<<std::endl;
                        std::cout << "Nombre archivo: '" << nombreArchivo << "'" << std::endl;
                        std::cout << "Segmentos:" << std::endl;
                        for (const std::string& seg : segmentos) {
                            std::cout << seg << " ";
                        }
                        std::cout << std::endl;

                    }
                }
            }
        }else if(comando.find("codificar_imagen") !=std::string::npos && comando.find("codificar_imagen")==0){
            if(comando[16]!=' '){
                std::cout<<"Argumento esperado [codificar_imagen <nombre_archivo.huf>]"<<std::endl;
            }
            else{
                comando.erase(0, 17);
                if(comando.size()==0){
                    std::cout<<"La imagen no ha podido ser codificada. Falta arg 1"<<std::endl;
                }else{
                    std::cout<<"La imagen en memoria ha sido codificada exitosamente y almacenada en el archivo '"<<comando<<"'"<<std::endl;
                }
            }


        }else if(comando.find("decodificar_archivo") !=std::string::npos && comando.find("decodificar_archivo")==0){
            if(comando[19]!=' '){
                std::cout<<"Argumento esperado [decodificar_archivo <nombre_archivo.huf> <nombre_imagen.pgm>]"<<std::endl;
            }
            else{
                comando.erase(0, 20);
                if(comando.size()==0){
                    std::cout<<"El archivo no ha podido ser decodificado. Falta argumento 1"<<std::endl;
                }else{
                    std::string nombreArchivo = comando.substr(0, comando.find(' '));
                    comando.erase(0, nombreArchivo.size()+1);
                    if(comando.size()==0){
                        std::cout<<"El archivo '"<<nombreArchivo<<"' no ha podido ser decodificado. Falta argumento 1"<<std::endl;
                    }
                    else{
                        comando.erase(0, comando.find(' ')+1);
                        std::cout<<"El archivo '"<<nombreArchivo<<"' ha sido decodificado exitosamente, y la imagen correspondiente se ha almacenado en el archivo '"<<comando<<"'"<<std::endl;
                    }
                }
            }

        }else if(comando.find("ayuda") !=std::string::npos && comando.find("ayuda")==0){
            comando.erase(0, 6);
            if(comando.size()==0){
                std::cout<<"Ayuda general:"<<std::endl
                <<"Lista de comandos:"<<std::endl
                <<"cargar_imagen:"<<std::endl;
                std::cout<<"Uso del comando: [cargar_imagen <nombre_imagen.pgm>]"<<std::endl;
                std::cout<<"El comando carga en memoria (en la estructura más adecuada) la imagen identificada ";
                std::cout<<"con el nombre_imagen.pgm"<<std::endl<<std::endl;
                
                std::cout<<"cargar_volumen:"<<std::endl;
                std::cout<<"Uso del comando: [cargar_volumen <nombre_base> <n_im>]"<<std::endl;
                std::cout<<"El comando carga en memoria la serie ordenada de ";
                std::cout<<"imágenes identificada con el nombre_base y cuyo tamaño corresponde a n_im imágenes (la serie ";
                std::cout<<"podrá tener máximo 99 imágenes). "<<std::endl<<std::endl;

                std::cout<<"info_imagen"<<std::endl;
                std::cout<<"Uso del comando: [info_imagen]"<<std::endl;
                std::cout<<"El comando muestra en pantalla la información básica de la imagen actualmente ";
                std::cout<<"cargada en memoria."<<std::endl<<std::endl;


                std::cout<<"info_volumen"<<std::endl;
                std::cout<<"Uso deo comando: [info_volumen]"<<std::endl;
                std::cout<<"El comando muestra en pantalla la información básica del volumen (serie de imágenes) ";
                std::cout<<"cargado actualmente en memoria"<<std::endl<<std::endl;


                std::cout<<"proyeccion2D"<<std::endl;
                std::cout<<"Uso del comando: [proyeccion2D <dirección> <criterio> <nombre_archivo.pgm>]"<<std::endl;
                std::cout<<"El comando debe tomar la serie ordenada de imágenes (ya cargada en memoria), y de ";
                std::cout<<"acuerdo a la dirección especificada por el usuario, debe recorrer cada posición en el plano perpendicular ";
                std::cout<<"a la dirección dada, y para cada una de esas posiciones debe colapsar toda la información existente en la ";
                std::cout<<"dirección dada utilizando el criterio especificado."<<std::endl<<std::endl;

                std::cout<<"codificar_imagen"<<std::endl;
                std::cout<<"Uso del comando: [decodificar_archivo <nombre_archivo.huf> <nombre_imagen.pgm>]"<<std::endl;
                std::cout<<"El comando debe generar el archivo de texto con la correspondiente codificación de Huffman para la imagen que se encuentre actualmente cargada en memoria, almacenándolo en disco bajo el nombre nombre_archivo.huf "<<std::endl<<std::endl;

                std::cout<<"decodificar_archivo"<<std::endl;
                std::cout<<"Uso del comando: [decodificar_archivo <nombre_archivo.huf> <nombre_imagen.pgm>]"<<std::endl;
                std::cout<<"El comando carga en memoria (en la estructura más adecuada) la información de codificación contenida en el archivo nombre_archivo.huf y luego debe generar la correspondiente imagen decodificada en formato PGM,"<<std::endl<<std::endl;

                std::cout<<"segmentar"<<std::endl;
                std::cout<<"Uso del comando: [segmentar <salida_imagen.pgm> <sx1> <sy1> <sl1> <sx2> <sy2> <sl2> ...]"<<std::endl;
                std::cout<<"El comando carga la información del conjunto de semillas correspondiente a la imagen cargada en memoria, para luego proceder a su segmentación de acuerdo al algoritmo presentado anteriormente."<<std::endl<<std::endl;

                std::cout<<"'salir' para salir"<<std::endl<<std::endl;
                std::cout<<"Si necesita ayuda para un comando en especifico escriba 'ayuda <comando>'"<<std::endl;
            }
            else if(comando.find("cargar_imagen")!=std::string::npos){
                std::cout<<"Ayuda para el comando [cargar_imagen]:"<<std::endl
                <<"Uso del comando: [cargar_imagen <nombre_imagen.pgm>]"<<std::endl;
                std::cout<<"posibles salidas en pantalla:"<<std::endl;
                std::cout<<"(proceso satisfactorio) La imagen nombre_imagen.pgm ha sido cargada."<<std::endl;
                std::cout<<"(mensaje de error) La imagen nombre_imagen.pgm no ha podido ser cargada."<<std::endl;
                std::cout<<"descripción: El comando carga en memoria la imagen identificada ";
                std::cout<<"con el nombre_imagen.pgm . Una vez cargada la información en memoria, el comando muestra el ";
                std::cout<<"mensaje de carga satisfactoria. Si por alguna razón no es posible cargar la imagen (nombre de archivo ";
                std::cout<<"erróneo o no existe), el comando muestra el mensaje de error. Solo es posible cargar una única ";
                std::cout<<"imagen por sesión, de tal forma que si el comando es llamado nuevamente con otro nombre de archivo, ";
                std::cout<<"la nueva imagen sobreescribe en memoria a la que ya estaba cargada anteriormente."<<std::endl<<std::endl;
            }
            else if(comando.find("cargar_volumen")!=std::string::npos){
                std::cout<<"Ayuda para el comando [cargar_volumen]:"<<std::endl
                <<"Uso del comando: [cargar_volumen <nombre_base> <n_im>]"<<std::endl;
                std::cout<<"salida en pantalla:"<<std::endl;
                std::cout<<"(proceso satisfactorio) El volumen nombre_base ha sido cargado."<<std::endl;
                std::cout<<"(mensaje de error) El volumen nombre_base no ha podido ser cargado."<<std::endl;
                std::cout<<"El comando carga en memoria la serie ordenada de ";
                std::cout<<"imágenes identificada con el nombre_base y cuyo tamaño corresponde a n_im imágenes (la serie ";
                std::cout<<"podrá tener máximo 99 imágenes). Todas las imágenes de la serie deben estar nombradas como ";
                std::cout<<"nombre_base xx.pgm, donde xx corresponde a dos dígitos de identificación de la posición de la imagen ";
                std::cout<<"en la serie (varía en el rango 01 - n_im ). Una vez cargada toda la información en memoria, el comando ";
                std::cout<<"debe mostrar el mensaje de carga satisfactoria. Si por alguna razón no es posible cargar completamente ";
                std::cout<<"la serie ordenada de imágenes (nombre de base erróneo, cantidad de imágenes no corresponde, error en ";
                std::cout<<"alguna imagen), el comando debe mostrar el mensaje de error. Solo es posible cargar un único volumen ";
                std::cout<<"por sesión, de tal forma que si el comando es llamado nuevamente con otro nombre base, el nuevo ";
                std::cout<<"volumen sobreescribe en memoria al que ya estaba cargado anteriormente."<<std::endl<<std::endl;
            }
            else if(comando.find("info_volumen")!=std::string::npos){
                std::cout<<"Ayuda para el comando [info_volumen]:"<<std::endl;
                std::cout<<"salida en pantalla:"<<std::endl;
                std::cout<<"(proceso satisfactorio) Volumen cargado en memoria: nombre_base , tamaño: n_im , ancho: W , alto: H ."<<std::endl;
                std::cout<<"(mensaje de error) No hay un volumen cargado en memoria."<<std::endl;
                std::cout<<"descripción: El comando muestra en pantalla la información básica del volumen (serie de imágenes) cargado actualmente en memoria: nombre base, cantidad de imágenes, ancho en pixeles y alto en pixeles. Si no se ha cargado aún un volumen en memoria, el comando muestra el mensaje de error."<<std::endl;
            }
            else if(comando.find("info_imagen")!=std::string::npos){
                std::cout<<"Ayuda para el comando [info_imagen]:"<<std::endl
                <<"Muestra la información de una imagen previamente cargado en el programa."<<std::endl;
                std::cout<<"salida en pantalla:"<<std::endl;
                std::cout<<"(proceso satisfactorio) Imagen cargada en memoria: nombre_imagen.pgm , ancho: W , alto: H"<<std::endl;
                std::cout<<"(mensaje de error) No hay una imagen cargada en memoria."<<std::endl<<std::endl;
                std::cout<<"descripción: El comando muestra en pantalla la información básica de la imagen actualmente cargada en memoria: nombre de archivo, ancho en pixeles y alto en pixeles. Si no se ha cargado aún una imagen en memoria, el comando debe mostrar el mensaje de error."<<std::endl<<std::endl;
            }
            else if(comando.find("proyeccion2D")!=std::string::npos){
                std::cout<<"Ayuda para el comando [proyeccion2D]:"<<std::endl
                <<"Uso del comando: [proyeccion2D <dirección> <criterio> <nombre_archivo.pgm>]"<<std::endl;
                std::cout<<"salida en pantalla:"<<std::endl;
                std::cout<<"(proceso satisfactorio) La proyección 2D del volumen en memoria ha sido generada y almacenada en el archivo nombre_archivo.pgm ."<<std::endl;
                std::cout<<"(mensajes de error) El volumen aún no ha sido cargado en memoria."<<std::endl;
                std::cout<<"La proyección 2D del volumen en memoria no ha podido ser generada."<<std::endl;
                std::cout<<"descripción: El comando toma la serie ordenada de imágenes (ya cargada en memoria), y de acuerdo a la dirección especificada por el usuario, debe recorrer cada posición en el plano perpendicular a la dirección dada, y para cada una de esas posiciones debe colapsar toda la información existente en la ";
                std::cout<<"dirección dada utilizando el criterio especificado. Esto genera un único valor de píxel para cada posición ";
                std::cout<<"del plano perpendicular, generando así una imagen 2D con la proyección de la información en el volumen. ";
                std::cout<<"La dirección puede ser una entre x (en dirección de las columnas), y (en dirección de las filas) o z (en ";
                std::cout<<"dirección de la profundidad). El criterio puede ser uno entre minimo (el valor mínimo de intensidad), ";
                std::cout<<"maximo (el valor máximo de intensidad), promedio (el valor promedio de intensidad) o mediana (el ";
                std::cout<<"valor mediana de intensidad). Una vez generada la proyección, debe guardarse como imagen en formato ";
                std::cout<<"PGM como nombre_archivo.pgm . Es importante anotar que este comando solo puede funcionar sobre ";
                std::cout<<"volúmenes (series de imágenes)."<<std::endl;
                
                
            }
            else if(comando.find("decodificar_archivo")!=std::string::npos){
                std::cout<<"Ayuda para el comando [decodificar_archivo]:"<<std::endl
                <<"Uso del comando: [decodificar_archivo <nombre_archivo.huf> <nombre_imagen.pgm>]"<<std::endl;
                std::cout<<"salida en pantalla:"<<std::endl;
                std::cout<<"(proceso satisfactorio) El archivo nombre_archivo.huf ha sido decodificado exitosamente, ";
                std::cout<<"y la imagen correspondiente se ha almacenado en el archivo nombre_imagen.pgm."<<std::endl;
                std::cout<<"(mensaje de error) El archivo nombre_archivo.huf no ha podido ser decodificado."<<std::endl;
                std::cout<<"descripción: El comando carga en memoria la información de codificación contenida en el archivo nombre_archivo.huf y luego debe generar la correspondiente ";
                std::cout<<"imagen decodificada en formato PGM, almacenándola en disco bajo el nombre nombre_imagen.pgm . Si por alguna razón no es posible cargar la información de codificación (nombre de archivo erróneo o no ";
                std::cout<<"existe), o no es posible realizar el proceso de decodificación (mal formato del archivo), el comando debe mostrar el mensaje de error";
            }
            else if(comando.find("codificar_imagen")!=std::string::npos){
                std::cout<<"Ayuda para el comando [codificar_imagen]:"<<std::endl
                <<"Uso del comando: [codificar_imagen <nombre_archivo.huf>]"<<std::endl;
                std::cout<<"salida en pantalla:"<<std::endl;
                std::cout<<"(proceso satisfactorio) La imagen en memoria ha sido codificada exitosamente y almacenada en el archivo nombre_archivo.huf ."<<std::endl;
                std::cout<<"(mensaje de error) No hay una imagen cargada en memoria."<<std::endl;
                std::cout<<"descripción: El comando genera el archivo de texto con la correspondiente codificación de Huffman para la imagen que se encuentre actualmente cargada en memoria, almacenándolo en disco bajo el nombre nombre_archivo.huf . Si no se ha cargado aún una imagen en memoria, el comando debe mostrar el mensaje de error"<<std::endl<<std::endl;
            }
            else if(comando.find("segmentar")!=std::string::npos){
                std::cout<<"Ayuda para el comando [segmentar]:"<<std::endl
                <<"Uso del comando: [segmentar <salida_imagen.pgm> <sx1> <sy1> <sl1> <sx2> <sy2> <sl2> ...]"<<std::endl;
                std::cout<<"salida en pantalla:"<<std::endl;
                std::cout<<"(proceso satisfactorio) La imagen en memoria fue segmentada correctamente y almacenada en el archivo salida_imagen.pgm "<<std::endl;
                std::cout<<"(mensaje de error) No hay una imagen cargada en memoria. La imagen en memoria no pudo ser segmentada"<<std::endl;
                std::cout<<"descripción: El comando debe cargar la información del conjunto de semillas correspondiente a la imagen cargada en memoria, para luego proceder a su segmentación de acuerdo al algoritmo presentado anteriormente. El usuario puede ingresar un máximo de 5 semillas en el comando. La imagen con las etiquetas debe quedar guardada en salida_imagen.pgm . Si no se ha cargado aún una imagen en memoria, o por alguna razón no es posible realizar el proceso de segmentación (semillas mal ubicadas, problemas en la construcción del grafo), el comando debe mostrar el mensaje de error"<<std::endl<<std::endl;
            }
            else{
                std::cout<<"el comando ["<<comando<<"] no existe."<<std::endl
                <<"Escriba 'ayuda' para ver una lista de posibles comandos, o 'ayuda <comando>' para ver ayuda sobre un comando"<<std::endl;
            }
        }
        else{
            if(!comando.empty()&& comando!="salir"){
            std::cout<<"el comando ["<<comando<<"] no existe."<<std::endl
            <<"Escriba 'ayuda' para ver una lista de posibles comandos, o 'ayuda <comando>' para ver ayuda sobre un comando"<<std::endl;
            }
            
        }
    }
    return 0;
}
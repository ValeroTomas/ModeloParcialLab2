#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

///ESTRUCTURA CONSOLA
typedef struct
{
    int codigoProducto;
    char marca[50]; // Nintendo Switch, Xbox, Playstation
    float precioEnMiles;
    int stock;
    char modelo[50];// Común, Pro, Slim
} stConsola ;

///NODO CONSOLA
typedef struct nodoConsola
{
    stConsola dato ;
    struct nodoConsola * siguiente;
} nodoConsola;

///PROTOTIPADO
nodoConsola* inicLista();
nodoConsola* crearNodo(stConsola consola);
nodoConsola* ordenarStock(nodoConsola* lista, nodoConsola* nuevo);
stConsola cargarConsola();
void muestraLista(nodoConsola* lista);

int main()
{
    int opc = 1;
    char eleccion = 's';
    nodoConsola* listaConsolas = inicLista();
    nodoConsola* nuevoNodo;
    stConsola nuevaConsola;


    switch(opc)
    {

    case 1:

        while(eleccion == 's')
        {
            nuevaConsola = cargarConsola();
            nuevoNodo = crearNodo(nuevaConsola);
            listaConsolas = ordenarStock(listaConsolas, nuevoNodo);
            printf("\n Desea continuar? s/n");
            fflush(stdin);
            scanf("%c", &eleccion);
            system("cls");
        }
        muestraLista(listaConsolas);


        break;

    case 2:

        break;

    default:

        break;

    }
    return 0;
}

nodoConsola* inicLista()
{
    return NULL;
}

nodoConsola* crearNodo(stConsola consola)
{
    nodoConsola* aux = (nodoConsola*)malloc(sizeof(nodoConsola));
    aux->dato = consola;
    aux->siguiente = NULL;

    return aux;
}

nodoConsola* ordenarStock(nodoConsola* lista, nodoConsola* nuevo)
{

    nodoConsola* aux;
    aux = lista;
    int flag = 0;
    if(lista == NULL)
    {
        lista = nuevo;
    }
    else if(nuevo->dato.stock <= lista->dato.stock)
    {
        nuevo->siguiente = lista;
        lista = nuevo;
    }
    else
    {
        while(aux->siguiente != NULL)
        {
            if(nuevo->dato.stock >= aux->dato.stock && nuevo->dato.stock <= aux->siguiente->dato.stock && flag == 0)
            {
                nuevo->siguiente = aux->siguiente;
                aux->siguiente = nuevo;
                flag = 1;
            }
            else
            {
                aux=aux->siguiente;
            }
        }
        if(aux->siguiente == NULL && flag == 0)
        {
            aux->siguiente = nuevo;
            nuevo->siguiente = NULL;
            flag = 1;
        }


    }

    return lista;
}

///CargarConsola
stConsola cargarConsola()
{

    stConsola consola;
    int opc = 1;

    printf("\n -Ingrese marca-");
    printf("\n 1- Playstation \n 2- Xbox \n 3- Nintendo Switch \n **DEFAULT: PLAYSTATION**\n\n  ");
    fflush(stdin);
    scanf("%d", &opc);
    if(opc == 2)
    {
        strcpy(consola.marca, "Xbox");
    }
    else if(opc == 3)
    {
        strcpy(consola.marca, "Nintendo Switch");
    }
    else
    {
        strcpy(consola.marca, "Playstation");
    }
    system("cls");
    printf("\nLa marca elegida es: %s\n", consola.marca);
    system("pause");
    system("cls");

    printf("\n -Ingrese modelo-");
    printf("\n 1- Standard \n 2- Pro \n 3- Slim \n **DEFAULT: STANDARD**\n\n  ");
    fflush(stdin);
    scanf("%d", &opc);
    if(opc == 2)
    {
        strcpy(consola.modelo, "Pro");
    }
    else if(opc == 3)
    {
        strcpy(consola.modelo, "Slim");
    }
    else
    {
        strcpy(consola.modelo, "Standard");
    }
    system("cls");
    printf("\nEl modelo elegido es: %s \n", consola.modelo);
    system("pause");
    system("cls");

    printf("\n -Ingrese stock: ");
    fflush(stdin);
    scanf("%d", &consola.stock);

    printf("\n\n -Ingrese precio (en miles): ");
    fflush(stdin);
    scanf("%f", &consola.precioEnMiles);

    printf("\n\n -Ingrese codigo de producto: ");
    fflush(stdin);
    scanf("%d", &consola.codigoProducto);

    return consola;
}

void mostrarConsola(stConsola consola)
{

    printf("\n -CONSOLA- \n");
    printf("\n -Marca: %s", consola.marca);
    printf("\n -Modelo: %s", consola.modelo);
    printf("\n -Precio: %.2f", consola.precioEnMiles);
    printf("\n -Stock: %d", consola.stock);
    printf("\n -Codigo de producto: %d", consola.codigoProducto);
}

void muestraLista(nodoConsola* lista)
{

    nodoConsola* aux = lista;

    while (aux != NULL)
    {
        mostrarConsola(aux->dato);
        aux = aux->siguiente;
    }
}

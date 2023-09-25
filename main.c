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
    char modelo[50];// Com�n, Pro, Slim
} stConsola ;

///NODO CONSOLA
typedef struct nodoConsola
{
    stConsola dato ;
    struct nodoConsola * siguiente;
} nodoConsola;

///NODO DOBLE
typedef struct
{

    char Nombre[50];
    int mediodepago; //1 efectivo, 2 patacones, 3 dolar     ahorro
    float totalCompra;
} stCliente ;

typedef struct nodoCliente
{
    stCliente dato;
    struct nodoCliente* siguiente;
    struct nodoCliente* anterior;
} nodoCliente;


///PROTOTIPADO
nodoConsola* inicLista();
nodoConsola* crearNodo(stConsola consola);
nodoConsola* ordenarStock(nodoConsola* lista, nodoConsola* nuevo);
stConsola cargarConsola();
void muestraLista(nodoConsola* lista);
void mostrarPrecio(nodoConsola* lista, float precio);
void cargarAutoConsolas(stConsola consolas[]);
void cargarAutoClientes(stCliente clientes[]);
int comprobarPredido(nodoConsola* lista, char marca[], char modelo[], int pedido);
void mostrarClientes(stCliente cliente);
void mostrarListaClientes(nodoCliente* lista);

//NODOS DOBLES
nodoCliente *iniclistaCliente();
nodoCliente* cargaLista(nodoCliente* lista);
nodoCliente *crearNodoCliente(stCliente clienteNuevo);
nodoCliente* cargaListaClientes(nodoCliente* lista, nodoCliente* nuevoNodo);
float restaCompra(nodoConsola* listaConsola, int cantidadStock, char marca[], char modelo[]);


int main()
{

    nodoCliente* listaClientes = iniclistaCliente();
    nodoCliente* nuevoNodoCliente;
    int i = 0;
    int opc = 1;
    char eleccion = 's';
    float precio = 0;
    nodoConsola* listaConsolas = inicLista();
    nodoConsola* nuevoNodo;
    stConsola nuevaConsola;
    stConsola consolas[2];
    cargarAutoConsolas(consolas);
    char marca[] = "Xbox";
    char modelo[] = "Slim";
    int pedido = 0;
    int flag;
    stCliente clientes[3];
    int flagVenta;
    char nombreBuscar[40];
    int metodoPagoBuscar;

    while(i<=2)
    {
        //nuevaConsola = cargarConsola();
        nuevoNodo = crearNodo(consolas[i]);
        listaConsolas = ordenarStock(listaConsolas, nuevoNodo);
        i++;
    }
    i = 0;

    fflush(stdin);
    scanf("%d", &opc);
    switch(opc)
    {

    case 1:
        muestraLista(listaConsolas);
        system("PAUSE");
        system("cls");
        break;

    case 2:

        printf("Mostrar precio: ");
        fflush(stdin);
        scanf("%f", &precio);
        mostrarPrecio(listaConsolas, precio);
        break;

    case 3:

        printf("\nIngrese stock a comprobar: ");
        fflush(stdin);
        scanf("%d", &pedido);
        flag = comprobarPredido(listaConsolas, marca, modelo, pedido);
        if(flag == 1)
        {
            printf("\nHay stock disponible.");
        }
        else
        {
            printf("\nNo hay stock disponible.");
        }

        break;

    case 4:

        cargarAutoClientes(clientes);
        while(i <= 2)
        {
            nuevoNodoCliente = crearNodoCliente(clientes[i]);
            listaClientes = cargaListaClientes(listaClientes, nuevoNodoCliente);
            //mostrarListaClientes(listaClientes);
            i++;
        }
        mostrarListaClientes(listaClientes);


        printf("\n\n\nINGRESE EL NOMBRE DEL CLIENTE: ");
        fflush(stdin);
        gets(nombreBuscar);

        printf("INGRESE SU METODO DE PAGO: ");
        fflush(stdin);
        scanf("%i", &metodoPagoBuscar);

        flagVenta = venta(listaConsolas, listaClientes, nombreBuscar, metodoPagoBuscar);


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

nodoCliente *iniclistaCliente()
{
    return NULL;
}

nodoCliente* crearNodoCliente(stCliente clienteNuevo)
{
    nodoCliente* aux = (nodoCliente*)malloc(sizeof(nodoCliente));
    aux->siguiente = NULL;
    aux->anterior = NULL;
    aux->dato = clienteNuevo;

    return aux;
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

    printf("\n-Ingrese marca-");
    printf("\n1- Playstation \n2- Xbox \n3- Nintendo Switch \n\n**DEFAULT: PLAYSTATION**\n\nOpcion: ");
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
    printf("\nLa marca elegida es: %s\n\n", consola.marca);
    system("pause");
    system("cls");

    printf("\n -Ingrese modelo-");
    printf("\n1- Standard \n2- Pro\n3- Slim \n\n**DEFAULT: STANDARD**\n\nOpcion: ");
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
    printf("\nEl modelo elegido es: %s \n\n", consola.modelo);
    system("pause");
    system("cls");

    printf("\n-Ingrese stock: ");
    fflush(stdin);
    scanf("%d", &consola.stock);

    printf("\n\n-Ingrese precio (en miles): ");
    fflush(stdin);
    scanf("%f", &consola.precioEnMiles);

    printf("\n\n-Ingrese codigo de producto: ");
    fflush(stdin);
    scanf("%d", &consola.codigoProducto);

    return consola;
}

void mostrarConsola(stConsola consola)
{

    printf("\n -CONSOLA-");
    printf("\n -Marca: %s", consola.marca);
    printf("\n -Modelo: %s", consola.modelo);
    printf("\n -Precio: %.3f", consola.precioEnMiles);
    printf("\n -Stock: %d", consola.stock);
    printf("\n -Codigo de producto: %d\n", consola.codigoProducto);
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

void mostrarPrecio(nodoConsola* lista, float precio)
{

    nodoConsola* aux = lista;

    if(aux)
    {
        if(aux->dato.precioEnMiles == precio)
        {
            mostrarConsola(aux->dato);
        }
        mostrarPrecio(aux->siguiente, precio);
    }

}

void cargarAutoConsolas(stConsola consolas[])
{
    strcpy(consolas[0].marca, "Playstation");
    strcpy(consolas[0].modelo, "Pro");
    consolas[0].precioEnMiles = 165.000;
    consolas[0].codigoProducto = 1;
    consolas[0].stock = 15;

    strcpy(consolas[1].marca, "Nintendo Switch");
    strcpy(consolas[1].modelo, "Standard");
    consolas[1].precioEnMiles = 255.000;
    consolas[1].codigoProducto = 2;
    consolas[1].stock = 4;

    strcpy(consolas[2].marca, "Xbox");
    strcpy(consolas[2].modelo, "Slim");
    consolas[2].precioEnMiles = 190.000;
    consolas[2].codigoProducto = 3;
    consolas[2].stock = 5;
}

void cargarAutoClientes(stCliente clientes[])
{
    strcpy(clientes[0].Nombre, "Fran");
    clientes[0].mediodepago = 1;
    clientes[0].totalCompra = 0;

    strcpy(clientes[1].Nombre, "Juan");
    clientes[1].mediodepago = 1;
    clientes[1].totalCompra = 0;

    strcpy(clientes[2].Nombre, "Pedro");
    clientes[2].mediodepago = 2;
    clientes[2].totalCompra = 0;

}

int comprobarPredido(nodoConsola* lista, char marca[], char modelo[], int pedido)
{
    int flag = 0;
    nodoConsola* aux = lista;
    while(aux)
    {
        if(strcmp(aux->dato.marca, marca) == 0 && strcmp(aux->dato.modelo, modelo) == 0)
        {

            if(pedido <= aux->dato.stock)
            {
                flag = 1;
            }
        }
        aux = aux->siguiente;
    }
    return flag;
}

void mostrarClientes(stCliente cliente)
{
    printf("\n-CLIENTE-");
    printf("\n-NOMBRE: %s", cliente.Nombre);
    printf("\n-METODO DE PAGO: %d", cliente.mediodepago);
    printf("\n-TOTAL: %f\n", cliente.totalCompra);
}

void mostrarListaClientes(nodoCliente* lista)
{

    nodoCliente* aux = lista;
    while(aux != NULL)
    {
        mostrarClientes(aux->dato);
        aux = aux->siguiente;
    }

}

nodoCliente* cargaListaClientes(nodoCliente* lista, nodoCliente* nuevoNodo)
{
    nodoCliente* aux = lista;
    if(!lista)
    {
        lista = nuevoNodo;
    }
    else
    {
        while(aux->siguiente != NULL)
        {
            aux = aux->siguiente;

        }
        aux->siguiente = nuevoNodo;
        nuevoNodo->anterior = aux;
    }

    return lista;
}

int venta(nodoConsola* listaConsola, nodoCliente* listaCliente, char nombre[], int medioPago)
{
    nodoCliente* aux = listaCliente;
    char marcaBuscar[30];
    char modeloBuscar[30];
    int cantidadStock;

    int flag = 0;

    if(aux)
    {
        while(aux->siguiente)
        {
            if(strcmp(aux->dato.Nombre, nombre)==0 && aux->dato.mediodepago == medioPago)
            {
                printf("\QUE MARCA BUSCA? ");
                fflush(stdin);
                gets(marcaBuscar);

                printf("\QUE MODELO BUSCA? ");
                fflush(stdin);
                gets(modeloBuscar);

                printf("CUANTAS CONSOLAS? ");
                fflush(stdin);
                scanf("%i", &cantidadStock);

                flag = comprobarPredido(listaConsola, marcaBuscar, modeloBuscar, cantidadStock);
            }
            aux = aux->siguiente;
        }
    }

    float total;
    if(flag == 1)
    {
        total = restaCompra(listaConsola, cantidadStock, marcaBuscar, modeloBuscar);
        muestraLista(listaConsola);
        printf("TOTAL A PAGAR = %f", total);
    }

    return flag;
}

float restaCompra(nodoConsola* listaConsola, int cantidadStock, char marca[], char modelo[])
{
    float total;
    nodoConsola* aux = listaConsola;
    while(aux)
    {
        if(strcmp(aux->dato.marca, marca) == 0 && strcmp(aux->dato.modelo, modelo) == 0)
        {
            aux->dato.stock = aux->dato.stock - cantidadStock;
            total = cantidadStock * aux->dato.precioEnMiles;
        }
        aux = aux->siguiente;
    }
    return total;
}



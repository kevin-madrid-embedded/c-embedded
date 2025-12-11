#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef struct
{
    unsigned char *Buffer;
    unsigned long Elements;
    unsigned long Head;
    unsigned long Tail;
    unsigned char Empty;
    unsigned char Full;
    //add more elements if necesary 
} AppBuffer_Buffer;

size_t count = 0;

void AppBuffer_printBuffer( AppBuffer_Buffer *hbuffer ){

    if(hbuffer == NULL)return;
    if(hbuffer->Empty != 0)return ;

    unsigned long next = hbuffer->Tail;
    printf("Print ring buffer contents: ");
    if((hbuffer->Head == hbuffer->Tail) && (hbuffer->Full == 1)){
        printf(" 0x%x ",hbuffer->Buffer[next]); 
        next = (next + 1) % hbuffer->Elements;
    }
    while(next != hbuffer->Head){
        printf(" 0x%x ",hbuffer->Buffer[next]); 
        next = (next + 1) % hbuffer->Elements;
    }
    printf("\n");
}
void AppBuffer_initBuffer( AppBuffer_Buffer *hbuffer ){

    if(hbuffer == NULL)return;

    hbuffer->Head = 0;
    hbuffer->Tail = 0;
    hbuffer->Empty = 1;
    hbuffer->Full = 0;
}
void AppBuffer_writeData( AppBuffer_Buffer *hbuffer, unsigned char data ){
    
    if(hbuffer == NULL)return;
    if(hbuffer->Full != 0)return;

    hbuffer->Buffer[hbuffer->Head] = data; 
    hbuffer->Head = (hbuffer->Head + 1) % hbuffer->Elements;
    if(hbuffer->Head == hbuffer->Tail){
        hbuffer->Full = 1; 
    }
    hbuffer->Empty = 0;
}

unsigned char AppBuffer_readData( AppBuffer_Buffer *hbuffer ){

    if(hbuffer == NULL)return 0;
    if(hbuffer->Empty != 0)return 0;

    unsigned char output = 0;

    output = hbuffer->Buffer[hbuffer->Tail];
    hbuffer->Tail = (hbuffer->Tail +1)% hbuffer->Elements;//If(Tail+1 == Elements)tail = 0; else tail++;
    if(hbuffer->Tail == hbuffer->Head){
        hbuffer->Empty = 1; 
    }
    hbuffer->Full = 0;
    return output;
}

unsigned char AppBuffer_isBufferEmpty( AppBuffer_Buffer *hbuffer ){
    if(hbuffer == NULL)return 0;
    if(hbuffer->Empty != 0)return 1;
    else return 0;
}
void test__AppBuffer_initBuffer__buffer_intilization( void )
{
    unsigned char arreglo[200];
    AppBuffer_Buffer  CircBuffer;
    CircBuffer.Buffer = arreglo;
    CircBuffer.Elements = 200u;
    AppBuffer_initBuffer( &CircBuffer );
    /*test cases*/
    assert( CircBuffer.Head == 0 );
    assert( CircBuffer.Tail == 0 );
    assert( CircBuffer.Empty == 1 );
    assert( CircBuffer.Full == 0 );
    /*if program reach up to here all tested passed*/
    printf("test buffer intialization succeed\n");
}
void test__AppBuffer_writeData__writting_a_single_data( void )
{
    unsigned char arreglo[200];
    AppBuffer_Buffer  CircBuffer;
    CircBuffer.Buffer = arreglo;
    CircBuffer.Elements = 3u;
    AppBuffer_initBuffer( &CircBuffer );
    AppBuffer_writeData( &CircBuffer, 0x23 );
    AppBuffer_printBuffer( &CircBuffer);
    
    assert( CircBuffer.Head == 1 ); //test head pointer increment by one
    assert( arreglo[CircBuffer.Head-1] == 0x23 ); //keep in mid is a circular buffer
    assert( AppBuffer_isBufferEmpty( &CircBuffer ) == 0u );
    /*if program reach up to here all tested passed*/
    printf("test writting single data succeed\n");
}
void test__AppBuffer_writeData__filling_the_buffer( void )
{
    unsigned char arreglo[200];
    AppBuffer_Buffer  CircBuffer;
    CircBuffer.Buffer = arreglo;
    CircBuffer.Elements = 3u;
    AppBuffer_initBuffer( &CircBuffer );
    AppBuffer_writeData( &CircBuffer, 0x23 );  //first element
    AppBuffer_writeData( &CircBuffer, 0x23 );  //second element
    AppBuffer_writeData( &CircBuffer, 0x23 );  //third element

    assert( CircBuffer.Full == 1 );  //test full flag
    assert( CircBuffer.Head == 0 );  //test head pointer roll over back to zero
    /*if program reach up to here all tested passed*/
    printf("test filling the buffer succeed\n");
    AppBuffer_printBuffer( &CircBuffer);
}
void test__AppBuffer_writeData__filling_the_buffer_different_data( void )
{
    unsigned char arreglo[200];
    AppBuffer_Buffer  CircBuffer;
    CircBuffer.Buffer = arreglo;
    CircBuffer.Elements = 40u;
    AppBuffer_initBuffer( &CircBuffer );
    unsigned char data = 0x23;
    for(size_t i=0;i<CircBuffer.Elements;i++){
        AppBuffer_writeData( &CircBuffer, data );
	data++;
    }
    AppBuffer_printBuffer( &CircBuffer);
}
int main(){
    
    unsigned char dato;
    unsigned char data;
    unsigned char arreglo[200];
    AppBuffer_Buffer  CircBuffer;
    
    //inicialización
    CircBuffer.Buffer = arreglo;
    CircBuffer.Elements = sizeof(arreglo)/sizeof(arreglo[0]);
    AppBuffer_initBuffer( &CircBuffer );
    
    //writting in the buffer
    dato = 100;
    AppBuffer_writeData( &CircBuffer, dato );
    dato = 120;
    AppBuffer_writeData( &CircBuffer, dato );
    dato = 200;
    AppBuffer_writeData( &CircBuffer, dato );
    
    //read all the messages 
    while( AppBuffer_isBufferEmpty( &CircBuffer ) == 0u )
    {
        data = AppBuffer_readData( &CircBuffer );
        printf( "data read from the queue %d\n", data );
    }
    
    test__AppBuffer_initBuffer__buffer_intilization();
    test__AppBuffer_writeData__writting_a_single_data();
    test__AppBuffer_writeData__filling_the_buffer();
    test__AppBuffer_writeData__filling_the_buffer_different_data();
}



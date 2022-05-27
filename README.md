# General
MasterMind game implementation in C Language.

# Game Rules
In questo gioco vi sono due giocatori, il codificatore e il decodificatore. 
Il codificatore deve comporre un codice formato da 3 o 4 cifre.
Il codificatore ha a disposizione, per comporre il codice segreto, un certo numero di cifre da 0 a 9.
Dopo che il codificatore ha composto il codice, il decodificatore cerca di indovinare il codice. 
Il codificatore, appena il suo avversario ha completato il tentativo, fornisce degli aiuti comunicando:

- Il numero di cifre giuste al posto giusto, cioè le cifre del tentativo che sono presenti nel codice
 al posto tentato.
- Il numero di cifre giuste al posto sbagliato, cioè le cifre del tentativo che sono si presenti nel codice 
ma non al posto tentato

Non bisogna comunicare quali cifre sono giuste o sbagliate ma solo quante. 
Se il decodificatore riesce ad indovinare il codice entro il numero di tentativi predeterminati allora quest'ultimo 
vince la partita, altrimenti vince il codificatore.

# How to Play my MasterMind
Il gioco e' cosi strutturato:

Inizializzazione della partita:
	Il giocatore, dal menu' principale, inserisce 1 per giocare la partita. 
	Dopo di che viene chiesto all'utente se caricare l'ultima partita salvata oppure 
	se iniziare una nuova partita. Nel caso il giocatore voglia continuare una partita 
	allora comincerà direttamente a giocare, altrimenti viene 
	richiesto di inserire il livello di difficoltà.

Fase di Gioco:
	L'utente può tornare al MENU senza salvare, SALVARE la partita 
	oppure inserire il proprio tentativo. L'utente inserisce un elemento del suo 
	tentativo alla volta. Per ogni tentativo viene restituito 
	all'utente il risultato e può proseguire. Per sapere quanti tentativi sono rimasti, 
	l'utente può basarsi sui tentativi non riempiti nel tabellone di gioco.

Parametri del gioco a seconda della difficolta':

PRINCIPIANTE:                                                        
	- lunghezza del codice da indovinare: 3 cifre                       
	- numero di tentativi ammessi: 20                                   
	- cifre ripetute: no                                                
	- cifre possibili presenti nel codice: 0, 1, 2, 3, 4, 5             
	
INTERMEDIO:                                                        
	- lunghezza del codice da indovinare: 4 cifre                       
	- numero di tentativi ammessi: 15                                  
	- cifre ripetute: no                                               
	- cifre possibili presenti nel codice: 0, 1, 2, 3, 4, 5, 6, 7      

AVANZATO:                                                           
	- lunghezza del codice da indovinare: 4 cifre                        
	- numero di tentativi ammessi: 9                                     
	- cifre ripetute: si                                                
	- cifre possibili presenti nel codice: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 

# Run the game
First of all run
    
	git clone https://github.com/mattiacurri/mastermind-C

Then you need an IDE that support MinGW compiler. I used Eclipse for this project
	(https://www.eclipse.org/downloads/) because it makes automatically the MakeFile configuration to link the resources.
In "saveGame.h", "rules.h", "top10.h" you need to insert respectively the path of "rules.txt", "howToPlay.txt", "match.dat", "bastop10.dat", "inttop10.dat", "advtop10.dat" according to where you are going to save this file, note that the game generates "match.dat" when you save, in savedMatch folder.

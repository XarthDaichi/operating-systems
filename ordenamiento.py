

def relacion(a,b):
	return a < b # Aqui puede ir cualquier relación TOTAL que se desee


## Algoritmo de la primera demostración del video... (por si lo quieren ver)
# Burbuja
def burbuja(L):
	hayCambios = 1
	while hayCambios: 
		hayCambios = 0
		for i in range(len(L)-1):
			if relacion(L[i+1],L[i]): #Si el de adelante le gana al de atrás
				T = L[i] 	#Entonces los cambio (P->Q)
				L[i] = L[i+1]
				L[i+1] = T
				hayCambios+=1 #Cada vez que hago una inversión, sumo uno
		#Si llego acá y no hubo cambios, elimino todas las "flechas"
	return L #El camino hamiltoniano

## Algoritmo de la primera demostración
def insercion(L):
	if L==[]: return []
	LO = insercion(L[1:])
	for i in range(len(LO)):
		if(relacion(L[0],LO[i])):
			LO.insert(i,L[0])  #Cuando lo encuentra, al que le gana, lo pone en medio
			return LO  #Lo retorna una vez que encuentra a quien le ganó
	LO.append(L[0])  #Si no, "perdió" con todos, lo pongo al final
	return LO


## Algoritmo de la segunda demostración
def quicksort(L):
	if(L==[]): return []
	Vic = []
	Per = []
	for i in L[1:]:
		if (relacion(i,L[0])): Vic.append(i)  #Compara L[0] con los demás, si alguno le "gana" va a Vic
		else: Per.append(i)                   # Si no, entonces va a Per
	Vic = quicksort(Vic) #Le encuentra el camino hamiltoniano a cada uno
	Per = quicksort(Per)
	return Vic+[L[0]]+Per #Lo pega...


Lista = [3,1,-5,7,3,9,-3]
# print(quicksort(Lista))
print(quicksort(Lista))

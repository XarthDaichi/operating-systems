> [!Sincronización]
> - Exclusión Mutua
> - Espera Acotada
> - Progreso

Algoritmos de sinconrización en sistemas distribuidos:
- Centralizada
	- Problemas: Peaje de escazú, todos se lo piden a una persona (sistema)
- Ring (Anillo/Aro)
	- Problemas: El mae que recibe el token se cae se pierde y es lento porque tiene que dar la vuelta
- Lamport 3(n-1)
- Optimal Algorithm 2(n-1)
	- Manda n-1 mensajes y espera a recibir n-1 mensajes para poder usar el recurso, siendo n la cantidad de procesos
- Grupos 2$\sqrt n$ 
	- El proceso le pregunta al lider del sitio y a todos, después de recibir los oks, lo envía a los demás líderes que se comunican con sus grupos y al tener todos los oks, mandan un ok devuelta al líder que se lo da al proceso inicial


CAP
3 características:
- Consistency: si el estado de los recursos es el mismo en todos los sitios
- Availability: que el recurso esté disponible
- Partition Tolerance: que tanto se puede distribuir un sistema, si una compu en el laboratorio se cae entonces no hay problema el resto van a seguir en pie

NO EXISTE UN SISTEMA QUE SEA CONSISTENTE; DISPONIBLE Y TOLERANTE A FALLOS

Se puede ver en un triangulo cada vertices es una de las tres características y un sistema solo puede estar en una arista
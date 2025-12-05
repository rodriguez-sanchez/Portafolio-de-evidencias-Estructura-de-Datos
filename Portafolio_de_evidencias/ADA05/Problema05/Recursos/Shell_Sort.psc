Algoritmo Shell_Sort
	Definir A Como Entero
	Definir N, gap, i, j, temp Como Entero
	Escribir 'Ingrese el tamaño del arreglo:'
	Leer N
	Dimensionar A(N)
	Para i<-1 Hasta N Con Paso 1 Hacer
		Escribir 'Ingrese el elemento ', i, ':'
		Leer A[i]
	FinPara
	gap <- Trunc(N/2)
	Mientras gap>0 Hacer
		Para i<-gap+1 Hasta N Con Paso 1 Hacer
			temp <- A[i]
			j <- i
			Mientras j>gap Y A[j-gap]>temp Hacer
				A[j] <- A[j-gap]
				j <- j-gap
			FinMientras
			A[j] <- temp
		FinPara
		gap <- Trunc(gap/2)
	FinMientras
	Escribir 'Arreglo ordenado:'
	Para i<-1 Hasta N Con Paso 1 Hacer
		Escribir A[i], ' 'Sin Saltar
	FinPara
	Escribir ''
FinAlgoritmo

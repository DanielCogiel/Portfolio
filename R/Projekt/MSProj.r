source("Functions.R")

ListaSzczegolowy = Zadanie_1A()
ListaSzczegolowy

ListaRozdzielczy = Zadanie_1B()
ListaRozdzielczy

plot(ListaRozdzielczy$HistogramL)
plot(ListaRozdzielczy$HistogramW)

#Zadanie 2

Zadanie2_ = Zadanie_2()
Zadanie2_
Zadanie2_$TestKolmogorowaLubuskie
Zadanie2_$TestKolmogorowaWielkopolskie

#Zadanie 3

Zadanie3_ = Zadanie_3()
Zadanie3_

# Zadanie 4

Zadanie4_ = Zadanie_4()
Zadanie4_

# Zadanie 5

Zadanie5_ = Zadanie_5()
Zadanie5_

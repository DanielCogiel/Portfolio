# Dane
lubuskie = c(23.27, 22.65, 24.3, 17.37, 16.52, 24.23, 18.37, 17.12, 20.16, 19.04, 24.15, 20.75, 19,
             18.24, 25.15, 20.7, 24.15, 20.95, 17.65, 15.83, 22.15, 23.98, 10.87, 21.13, 21.54, 24.1,
             17.42, 16.34, 20.03, 22.7, 13.38, 25.43, 20.02, 23.45, 19.7, 23, 19.37, 20.05, 17.57,
             23.67, 18.27, 16.26, 17.29, 14.97, 20.64, 14.19, 19.87, 17.07, 22.63, 19.09, 19.99)
wielkopolskie = c(19.3, 18.7, 21.32, 16.59, 15.86, 21.28, 15.8, 13, 15.38, 18.14, 19.24, 13.12, 17.18, 20.44,
                  13.12, 22.07, 22.03, 13.52, 16.09, 16.1, 22.37, 22, 17.6, 17.16, 19.84, 19.84, 21.26,
                  21.81, 17.35, 17.91, 17.42, 22.55, 19.57, 22.2, 18.16, 20.73, 20.07, 18.31, 19.09, 18.5,
                  20.72, 15.79, 14.4, 19.05, 25.11, 19.3, 18.51, 15.64)

# Funkcje
getmode <- function(v) {
  uniqv <- unique(v)
  uniqv[which.max(tabulate(match(v, uniqv)))]
}

#przedzialy= seq(range(lubuskie)[1], range(lubuskie)[2], (range(lubuskie)[2]-range(lubuskie)[1])/k)
wyznacz_przedzialy = function(vec, k)
{
  rezultat = seq(range(vec)[1], range(vec)[2], (range(vec)[2]-range(vec)[1])/k)
}

#skosnosc
skosnosc = function(vec) {
  #tsuma przechowuje sume szescianow roznicy kolejnych elementow tablicy i sredniej
  tsuma = 0
  for (i in 1:length(vec)) {
    tsuma = tsuma + (vec[i]-mean(vec))^3
  }
  tskosnosc = tsuma/(length(vec)*(sd(vec))^3)
  return(tskosnosc)
}

#kurtoza
kurtoza = function(vec) {
  #tsuma przechowuje sume podniesionej do potegi 4 roznicy kolejnych elementow tablicy i sredniej
  tsuma = 0
  for (i in 1:length(vec)) {
    tsuma = tsuma + (vec[i]-mean(vec))^4
  }
  tkurtoza = tsuma/(length(vec)*(sd(vec))^4)
  return(tkurtoza)
}

#odchylenie przeci?tne
odchylenie_przecietne = function(vec)
{
  wynik = sum(abs(vec - mean(vec))) / length(vec)
  return(wynik)
}

#kwantyl podanego rz?du
getQuantile = function(vec, type)
{
  sorted_vec =  sort(vec)
  index = round(type * (length(sorted_vec) + 1), digits = 1)
  wynik = sorted_vec[index]
  return (wynik)
}

# Obciazone
varO =  function(vec) {
  var(vec) * (length(vec) - 1) / length(vec) 
}

varNieobcRozdzielczy = function(histogram)
{
  liczebnosc = sum(histogram$counts)
  wynik = wariancjaRozdzielczy(histogram) * (liczebnosc / (liczebnosc - 1))
  return(wynik)
}

testKolmogorova <- function(wektor, war_krytyczna) {
  rnames <- c("x", "i/n", "F_0(x)", "|i/n - F_0(x)|", "|(i - 1)/n - F_0(x)|")
  cnames <- 1:length(wektor)
  tablicaKolmogorowa <- matrix(data = c(sort(wektor), numeric(length(wektor) * 4)), nrow = length(wektor),
                               ncol = 5, dimnames = list(cnames, rnames))
  for(i in 1:length(wektor)) {
    tablicaKolmogorowa[i, 2] = i/length(wektor)
    tablicaKolmogorowa[i, 3] = sort(pnorm(wektor, mean = mean(wektor), sd = sd(wektor)))[i]
    tablicaKolmogorowa[i, 4] = abs(tablicaKolmogorowa[i, 2] - tablicaKolmogorowa[i, 3])
    if (i > 1) tablicaKolmogorowa[i, 5] = abs(tablicaKolmogorowa[i - 1, 2] - tablicaKolmogorowa[i, 3])
    else tablicaKolmogorowa[i, 5] - 0;
  }
  max <- max(max(tablicaKolmogorowa[1:length(wektor), 4]), max(tablicaKolmogorowa[1:length(wektor), 5]))
  
  Komunikat = ""
  
  if (max > war_krytyczna & max < 1) {
    Komunikat = "Zawartości cukru nie mają rozkładu normalnego"
   
  } else {
    Komunikat = "Nie ma podstaw, aby odrzucić tezę, że zawartości cukru mają rozkład normalny"
    
  }
  wynik = list(TablicaKolmogorowa = tablicaKolmogorowa, Max = max, WarunekKrytyczny = war_krytyczna, Wniosek = Komunikat)
  return(wynik)
}

oszacujPrzedzialowoSrednia = function(wektor, wspolczynnik_ufnosci) {
  nWektor = numeric(2)
  wyrazenie = qt(1 - (1 - wspolczynnik_ufnosci)/2, length(wektor) - 1) * sd(wektor)/sqrt(length(wektor))
  nWektor[1] = mean(wektor) - wyrazenie
  nWektor[2] = mean(wektor) + wyrazenie
  return(nWektor) 
}

obliczPrecyzjeSzacunku = function(vec, p)
{
  przedzial = oszacujPrzedzialowoSrednia(vec, p)
  ln = przedzial[2]-przedzial[1]
  
  return(((ln/2)/mean(vec)) * 100)
}

wnioskowanieStatystyczne = function(p)
{
  Komunikat = ""
  if(p<5){
    Komunikat = "Uogolnienie na cala populacje jest calkowicie bezpieczne."
  } else if(p<10){
    Komunikat = "Uogolnienie na cala populacje jest watpliwe."
  } else{
    Komunikat = "Uogolnienie na cala populacje jest calkowicie niepewne."
  }
  return(Komunikat)
}
## Funckja zwraca 1 - dolny kres przedzialu, 2 - gorny kres przedzialu, 3 - wzgledna precyzje
oszacujPrzedzialowoOdchylenieIPrecyzje = function(wektor, wspolczynnik_ufnosci) {
  
  alfa = 1 - wspolczynnik_ufnosci
  dolnyKres = sqrt(((length(wektor)-1)*var(wektor))/qchisq(1 - alfa/2, length(wektor) - 1))
  gornyKres = sqrt(((length(wektor)-1)*var(wektor))/qchisq(alfa/2, length(wektor) - 1))
  wzglednaPrecyzja = (((gornyKres - dolnyKres)/2)/sd(wektor)) * 100
  return(list(DolnyKres = dolnyKres, GornyKres = gornyKres, WzglednaPrecyzja = wzglednaPrecyzja))
}

#Rozdzielczy
sredniaRozdzielczy = function(histogram) 
{
  wynik = sum(histogram$mids * histogram$counts) / sum(histogram$counts)
  return(wynik)
}

modaRozdzielczy = function(histogram)
{
  index = which.max(histogram$counts)
  x0 = histogram$breaks[index]
  n0 = histogram$counts[index]
  h0 = histogram$breaks[2] - histogram$breaks[1]
  nprev = histogram$counts[index - 1]
  nnext = histogram$counts[index + 1]
  return(x0 + (((n0 - nprev)*h0) / ((n0 - nprev) + (n0 - nnext))))
}

momentCentralnyRozdzielczy = function(histogram, k)
{
  wynik = sum(((histogram$mids-sredniaRozdzielczy(histogram)) ^ k) * histogram$counts) / sum(histogram$counts)
  return(wynik)
}

wariancjaRozdzielczy = function(histogram)
{
  wynik = momentCentralnyRozdzielczy(histogram, 2)
  return(wynik)
}

odchylenieStdRozdzielczy = function(histogram)
{
  wynik = sqrt(wariancjaRozdzielczy(histogram))
  return(wynik)
}

skosnoscRozdzielczy = function(histogram)
{
  wynik = momentCentralnyRozdzielczy(histogram, 3) / odchylenieStdRozdzielczy(histogram) ^ 3
  return (wynik)
}

kurtozaRozdzielczy = function(histogram)
{
  wynik = momentCentralnyRozdzielczy(histogram, 4) / odchylenieStdRozdzielczy(histogram) ^ 4
  return (wynik)
}
    
odchyleniePrzecietneRozdzielczy = function(histogram)
{
  wynik = sum((abs(histogram$mids-sredniaRozdzielczy(histogram))) * histogram$counts) / sum(histogram$counts)
  return(wynik)
}

kwantylRozdzielczy = function(histogram, qntValue)
{
  cumulatedCounts = numeric(length(histogram$counts))
  cumulatedCounts[1] = histogram$counts[1]
  for (i in 2:length(cumulatedCounts))
  {
    cumulatedCounts[i] = cumulatedCounts[i - 1] + histogram$counts[i]
  }
  indeksKwantyla = sum(histogram$counts) * qntValue
  indeksPrzedzialuKwantyla = 0
  znalezionoPrzedzialKwantyla = 0
  
  i = 1
  while (znalezionoPrzedzialKwantyla == 0)
  {
    if (cumulatedCounts[i] >= indeksKwantyla)
    {
      znalezionoPrzedzialKwantyla = 1
      indeksPrzedzialuKwantyla = i
    }
    i = i + 1
  }
  x0 = histogram$breaks[indeksPrzedzialuKwantyla]
  Nqnt = indeksKwantyla
  nIsk = cumulatedCounts[indeksPrzedzialuKwantyla - 1]
  hQnt = histogram$breaks[2] - histogram$breaks[1]
  nQnt = histogram$counts[indeksPrzedzialuKwantyla]
  
  wynik = x0 + (Nqnt - nIsk) * (hQnt / nQnt)
  return(wynik)
}

madRozdzielczy = function(histogram)
{
  mediana = kwantylRozdzielczy(histogram, 0.5)
  wynik = sum((abs(histogram$mids - mediana) * histogram$counts) / sum(histogram$counts))
  return(wynik)
}

Zadanie_1A = function()
{
  # Srednia
  SredniaL = mean(lubuskie)
  SredniaW = mean(wielkopolskie)
  
  # Mediana
  MedianaL = median(lubuskie)
  MedianaW = median(wielkopolskie)
  
  # Moda
  ModaL = getmode(lubuskie)
  ModaW = getmode(wielkopolskie)
  
  # Q1 i Q3
  KwartylQ1L = getQuantile(lubuskie, 0.25)
  KwartylQ3L = getQuantile(lubuskie, 0.75)
  KwartylQ1W = getQuantile(wielkopolskie, 0.25)
  KwartylQ3W = getQuantile(wielkopolskie, 0.75)
  
  # Zakres
  ZakresL = range(lubuskie)
  ZakresW = range(wielkopolskie)
  
  # Wariancja
  WariancjaL = var(lubuskie)
  WariancjaW = var(wielkopolskie)
  
  WariancjaObcL = varO(lubuskie)
  WariancjaObcW = varO(wielkopolskie)
  
  # Odchylenie standardowe
  OdchylenieStdL = sd(lubuskie)
  OdchylenieStdW = sd(wielkopolskie)
  
  # Obciazenie
  OdchylenieStdObcL = sqrt(varO(lubuskie))
  OdchylenieStdObcW = sqrt(varO(wielkopolskie))
  
  # Odchylenie przecietne - d1
  OdchyleniePrcL = odchylenie_przecietne(lubuskie)
  OdchyleniePrcW = odchylenie_przecietne(wielkopolskie)
  
  # Odchylenie przecietne od mediany - d2
  OdchyleniePrcOdMedianyL = mad(lubuskie)
  OdchyleniePrcOdMedianyW = mad(wielkopolskie)
  
  # Odchylenie cwiartkowe Q.D. = Q3 – Q1 / 2
  OdchylenieCwiartkoweL = (KwartylQ3L - KwartylQ1L) / 2
  OdchylenieCwiartkoweW = (KwartylQ3W - KwartylQ1W) / 2
  
  # Wspolczynnik Vs
  KlasycznyWspZmiennosciL = sd(lubuskie) / mean(lubuskie) * 100
  KlasycznyWspZmiennosciW = sd(wielkopolskie) / mean(wielkopolskie) * 100
  
  # Wspolczynnik Vq Vq=Q/Me Vq1,q2= (Q3-Q1)/(Q3+Q1)
  PozycyjnyWspZmiennosciL = KlasycznyWspZmiennosciL/median(lubuskie) 
  PozycyjnyWspZmiennosciW = KlasycznyWspZmiennosciW/median(wielkopolskie) 
  
  # Skosnosc g1
  SkosnoscL = skosnosc(lubuskie)
  SkosnoscW = skosnosc(wielkopolskie)
  
  # Kurtoza krt
  KurtozaL = kurtoza(lubuskie)
  KurtozaW = kurtoza(wielkopolskie)

  # Eksces porownnanie kurtozy danego rozkladu z kurtoza rozkladu normalnego g2
  EkscesL = KurtozaL - 3
  EkscesW = KurtozaW - 3
  
  wynik = list(SredniaL = SredniaL, MedianaL = MedianaL, ModaL = ModaL, KwartylQ1L = KwartylQ1L, 
               KwartylQ3L = KwartylQ3L, ZakresL = ZakresL, WariancjaL = WariancjaL, WariancjaObcL = WariancjaObcL,
               OdchylenieStdL = OdchylenieStdL, OdchylenieStdObcL = OdchylenieStdObcL, OdchyleniePrcL =  OdchyleniePrcL,
               OdchyleniePrcOdMedianyL = OdchyleniePrcOdMedianyL, OdchylenieCwiartkoweL = OdchylenieCwiartkoweL, 
               KlasycznyWspZmiennosciL = KlasycznyWspZmiennosciL, PozycyjnyWspZmiennosciL = PozycyjnyWspZmiennosciL,
               SkosnoscL = SkosnoscL, KurtozaL = KurtozaL, EkscesL = EkscesL, SredniaW = SredniaW, MedianaW = MedianaW, ModaW = ModaW, KwartylQ1W = KwartylQ1W, 
               KwartylQ3W = KwartylQ3W, ZakresW = ZakresW, WariancjaW = WariancjaW, WariancjaObcW = WariancjaObcW,
               OdchylenieStdW = OdchylenieStdW, OdchylenieStdObcW = OdchylenieStdObcW, OdchyleniePrcW =  OdchyleniePrcW,
               OdchyleniePrcOdMedianyW = OdchyleniePrcOdMedianyW, OdchylenieCwiartkoweW = OdchylenieCwiartkoweW, 
               KlasycznyWspZmiennosciW = KlasycznyWspZmiennosciW, PozycyjnyWspZmiennosciW = PozycyjnyWspZmiennosciW,
               SkosnoscW = SkosnoscW, KurtozaW = KurtozaW, EkscesW = EkscesW) 
  return(wynik)
}

Zadanie_1B = function() 
  {
  ######################### Rozdzielczy #############################
  # Liczebnosc przedzialow
  liczba_przedzialow = round(sqrt(length(lubuskie)))
  
  histogramL <- hist(lubuskie, breaks = wyznacz_przedzialy(lubuskie, liczba_przedzialow))
  histogramW <- hist(wielkopolskie, breaks = wyznacz_przedzialy(wielkopolskie, liczba_przedzialow))
  
  # Srednia
  SredniaL = sredniaRozdzielczy(histogramL)
  SredniaW = sredniaRozdzielczy(histogramW)
  
  # Mediana
  MedianaL = kwantylRozdzielczy(histogramL, 0.5)
  MedianaW = kwantylRozdzielczy(histogramW, 0.5)
  
  # Moda
  ModaL = modaRozdzielczy(histogramL)
  ModaW = modaRozdzielczy(histogramW)
  
  # Q1 i Q3
  KwartylQ1L = kwantylRozdzielczy(histogramL, 0.25)
  KwartylQ3L = kwantylRozdzielczy(histogramL, 0.75)
  KwartylQ1W = kwantylRozdzielczy(histogramW, 0.25)
  KwartylQ3W = kwantylRozdzielczy(histogramW, 0.75)
  
  # Zakres
  ZakresL = range(histogramL$breaks)
  ZakresW = range(histogramW$breaks)
  
  #Wariancja (Estymator nieobciążony)
  WariancjaL = varNieobcRozdzielczy(histogramL)
  WariancjaW = varNieobcRozdzielczy(histogramW)
  
  # Wariancja (Estymator obciążony)
  WariancjaObcL = wariancjaRozdzielczy(histogramL)
  WariancjaObcW = wariancjaRozdzielczy(histogramW)
  
  # Odchylenie standardowe (Estymator nieobciążony)
  OdchylenieStdL = sqrt(WariancjaL)
  OdchylenieStdW = sqrt(WariancjaW)
  
  # Odchylenie standardowe (Estymator obciążony)
  OdchylenieStdObcL = odchylenieStdRozdzielczy(histogramL)
  OdchylenieStdObcW = odchylenieStdRozdzielczy(histogramW)
  
  # Odchylenie przecietne - d1
  OdchyleniePrcL = odchyleniePrzecietneRozdzielczy(histogramL)
  OdchyleniePrcW = odchyleniePrzecietneRozdzielczy(histogramW)
  
  # Odchylenie przecietne od mediany - d2
  OdchyleniePrcOdMedianyL = madRozdzielczy(histogramL)
  OdchyleniePrcOdMedianyW = madRozdzielczy(histogramW)
  
  # Odchylenie cwiartkowe Q.D. = Q3 – Q1 / 2
  OdchylenieCwiartkoweL = (KwartylQ3L - KwartylQ1L) / 2
  OdchylenieCwiartkoweW = (KwartylQ3W - KwartylQ1W) / 2
  
  # Wspolczynnik Vs
  KlasycznyWspZmiennosciL = OdchylenieStdL / sredniaRozdzielczy(histogramL) * 100
  KlasycznyWspZmiennosciW = OdchylenieStdW / sredniaRozdzielczy(histogramW) * 100
  
  # Wspolczynnik Vq Vq=Q/Me Vq1,q2= (Q3-Q1)/(Q3+Q1)
  PozycyjnyWspZmiennosciL =  KlasycznyWspZmiennosciL / kwantylRozdzielczy(histogramL, 0.5) 
  PozycyjnyWspZmiennosciW =  KlasycznyWspZmiennosciW / kwantylRozdzielczy(histogramW, 0.5) 
  
  # Skosnosc g1
  SkosnoscL = skosnoscRozdzielczy(histogramL)
  SkosnoscW = skosnoscRozdzielczy(histogramW)
  
  # Kurtoza krt
  KurtozaL = kurtozaRozdzielczy(histogramL)
  KurtozaW = kurtozaRozdzielczy(histogramW)
  
  # Eksces porownnanie kurtozy danego rozkladu z kurtoza rozkladu normalnego g2
  EkscesL = KurtozaL - 3
  EkscesW = KurtozaW - 3
  
  wynik = list(SredniaL = SredniaL, MedianaL = MedianaL, ModaL = ModaL, KwartylQ1L = KwartylQ1L, 
               KwartylQ3L = KwartylQ3L, ZakresL = ZakresL, WariancjaL = WariancjaL, WariancjaObcL = WariancjaObcL,
               OdchylenieStdL = OdchylenieStdL, OdchylenieStdObcL = OdchylenieStdObcL, OdchyleniePrcL =  OdchyleniePrcL,
               OdchyleniePrcOdMedianyL = OdchyleniePrcOdMedianyL, OdchylenieCwiartkoweL = OdchylenieCwiartkoweL, 
               KlasycznyWspZmiennosciL = KlasycznyWspZmiennosciL, PozycyjnyWspZmiennosciL = PozycyjnyWspZmiennosciL,
               SkosnoscL = SkosnoscL, KurtozaL = KurtozaL, EkscesL = EkscesL, SredniaW = SredniaW, MedianaW = MedianaW, ModaW = ModaW, KwartylQ1W = KwartylQ1W, 
               KwartylQ3W = KwartylQ3W, ZakresW = ZakresW, WariancjaW = WariancjaW, WariancjaObcW = WariancjaObcW,
               OdchylenieStdW = OdchylenieStdW, OdchylenieStdObcW = OdchylenieStdObcW, OdchyleniePrcW =  OdchyleniePrcW,
               OdchyleniePrcOdMedianyW = OdchyleniePrcOdMedianyW, OdchylenieCwiartkoweW = OdchylenieCwiartkoweW, 
               KlasycznyWspZmiennosciW = KlasycznyWspZmiennosciW, PozycyjnyWspZmiennosciW = PozycyjnyWspZmiennosciW,
               SkosnoscW = SkosnoscW, KurtozaW = KurtozaW, EkscesW = EkscesW, HistogramL = histogramL, HistogramW = histogramW) 
  return(wynik)
}

Zadanie_2 = function()
{
  TestKolmogorowaLubuskie = testKolmogorova(lubuskie, 0.886/sqrt(length(lubuskie)));
  TestKolmogorowaWielkopolskie = testKolmogorova(wielkopolskie, 0.886/sqrt(length(wielkopolskie)));
  wynik = list(TestKolmogorowaLubuskie = TestKolmogorowaLubuskie, TestKolmogorowaWielkopolskie = TestKolmogorowaWielkopolskie)
  return(wynik)
}

Zadanie_3 = function()
{
  Przedzial = oszacujPrzedzialowoSrednia(lubuskie, 0.95)
  Precyzja = obliczPrecyzjeSzacunku(lubuskie, 0.95)
  Komunikat = wnioskowanieStatystyczne(Precyzja)
  wynik = list(PrzedzialSredniej = Przedzial, PrecyzjaSzacunku = Precyzja, Wniosek = Komunikat)
  return(wynik)
}

Zadanie_4 = function()
{
  estymacjaPrzedzialowa = oszacujPrzedzialowoOdchylenieIPrecyzje(wielkopolskie, 0.95)
  dolnyKres = estymacjaPrzedzialowa$DolnyKres
  gornyKres = estymacjaPrzedzialowa$GornyKres
  Przedzial = c(dolnyKres, gornyKres)
  precyzja = estymacjaPrzedzialowa$WzglednaPrecyzja
  Komunikat = wnioskowanieStatystyczne(estymacjaPrzedzialowa$WzglednaPrecyzja)
  return(list(PrzedzialOdchyleniaStandardowego = Przedzial, PrecyzjaSzacunku = precyzja, Wniosek = Komunikat))
}

Zadanie_5 = function()
{
  alfa = 0.05
  
  #Test dla wariancji
  F0 = var(lubuskie)/var(wielkopolskie)
  przedzial_krytyczny_1 = c(qf(1-alfa,length(lubuskie)-1,length(wielkopolskie)-1), Inf)
  F0
  przedzial_krytyczny_1
  
  #Test dla srednich
  wartoscStatytykiTestowej = (mean(lubuskie) - mean(wielkopolskie))/   
    sqrt(((length(lubuskie)-1)*var(lubuskie) + (length(wielkopolskie)-1)*var(wielkopolskie))/
           (length(lubuskie)+length(wielkopolskie)-2)*(1/length(lubuskie)+1/length(wielkopolskie)))
  przedzial_krytyczny = c(qt(1-alfa, length(lubuskie) + length(wielkopolskie) - 2), Inf)
  wartoscStatytykiTestowej
  przedzial_krytyczny
  return(list(PoziomIstotnosci = alfa, WartoscStatystykiTestowejDlaOdchylen = F0, 
              PrzedzialKrytycznyDlaOdchylen = przedzial_krytyczny_1,
              WartoscStatystykiTestowejDlaSrednich = wartoscStatytykiTestowej, 
              PrzedzialKrytycznyDlaSrednich = przedzial_krytyczny))
  
}




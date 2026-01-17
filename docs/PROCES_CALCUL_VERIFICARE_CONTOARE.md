# Proces de Calcul - Verificare Metrologică Contoare de Apă

## 1. Introducere

Acest document descrie procesul de calcul utilizat pentru verificarea metrologică a contoarelor de apă. Verificarea constă în măsurarea preciziei contorului prin compararea volumului indicat de contor cu un volum de referință obținut prin metode calibrate.

## 2. Configurare Inițială

Înainte de începerea măsurătorilor, se configurează:

- **Tipul contorului**: DN (diametru nominal), clasă metrologică, debite caracteristice (Q1, Q2, Q3)
- **Metoda de măsurare**: Volumetrică sau Gravimetrică
- **Metoda de corecție** (pentru gravimetrică): Clasică, INM sau ELCOST  (este setata la certificare)
- **Condiții ambientale**: Temperatură (t), Presiune (P), Umiditate

## 3. Procesul de Măsurare

Pentru fiecare măsurătoare (se efectuează până la 20 măsurători la diferite debite):

### 3.1. Pași de măsurare

1. Se notează **indexul inițial** al contorului: `Index_Start` [L]
2. Apa trece prin contor și este colectată:
   - **Metodă volumetrică**: foloseste un debitmetru electromagnetic ca etalon secundar pentru contorizarea volumului conventional adevarat
   - **Metodă gravimetrică**: foloseste o balanta de precizie pentru masurarea masei de apa ce este apoi convertita in volum
3. Se măsoară parametrii specifici metodei (vezi secțiunea 4)
4. Se notează **indexul final** al contorului: `Index_Stop` [L]
5. Se calculează volumul de referință și eroarea

### 3.2. Date înregistrate

- Index Start și Index Stop [L]
- **Pentru metoda volumetrică**: Volumul etalon [L]
- **Pentru metoda gravimetrică**: Masă apă colectată [kg], Temperatură apă [°C]

## 4. Calcul Volum de Referință

Volumul de referință reprezintă volumul real de apă care a trecut prin contor, calculat independent de indicația contorului.

### 4.1. Metoda Volumetrică

Apa trece prin contorul verificat și este colectată într-un rezervor etalon calibrat. **Valoarea convențional adevărată este cea citită pe debitmetrul folosit ca etalon secundar** (nu volumul rezervorului).

```
V_referință = V_debitmetru_etalon [L]
```

**Principiu**: Debitmetrul etalon secundar măsoară volumul real de apă care a trecut prin sistem, această valoare fiind considerată referința metrologică pentru calculul erorii contorului testat.

### 4.2. Metoda Gravimetrică - Variantă CLASICĂ

Apa este cântărită, iar masa se convertește în volum folosind un factor de corecție dependent de temperatură.

```
V_referință = K(t) × m
```

Unde:
- `m` = masa apei măsurată [kg]
- `t` = temperatura apei [°C]
- `K(t)` = factor de conversie [L/kg]

**Factorul K(t)** este o funcție de temperatură care compensează variația densității apei cu temperatura și include efectul forței arhimedice. Se obține prin interpolare din tabele metrologice standard (de exemplu, tabelele OIML R49).

### 4.3. Beneficiarul poate conveni cu BRML/INM obținerea certificatului de etalonare a instalației folosind alte metode puse la dispoziție de acest program.

## 5. Calcul Eroare

După determinarea volumului de referință, se calculează eroarea contorului.

### 5.1. Formula Generală

```
Eroare = [(Index_Stop - Index_Start) - V_referință] / V_referință × 100 [%]
```

Sau echivalent:

```
Eroare = [(V_indicat - V_referință) / V_referință] × 100 [%]
```

Unde:
- `V_indicat` = Index_Stop - Index_Start = volumul afișat de contor [L]
- `V_referință` = volumul real calculat prin metoda aleasă [L]

### 5.2. Interpretare

- **Eroare pozitivă** (+): Contorul indică mai mult decât volumul real → contorul "grăbește"
- **Eroare negativă** (−): Contorul indică mai puțin decât volumul real → contorul "întârzie"
- **Eroare = 0%**: Contorul este perfect calibrat (situație teoretică)

### 5.3. Exemple

**Exemplu 1**: Metodă volumetrică
- Index_Start = 1000.00 L
- Index_Stop = 1050.00 L
- V_etalon = 50.00 L
- V_indicat = 1050.00 - 1000.00 = 50.00 L
- Eroare = (50.00 - 50.00) / 50.00 × 100 = **0.00%** ✓

**Exemplu 2**: Metodă gravimetrică clasică
- Index_Start = 2000.00 L
- Index_Stop = 2100.50 L
- Masă = 100.00 kg
- Temperatură = 20°C → K(t=20°C) ≈ 1.002 L/kg
- V_referință = 1.002 × 100.00 = 100.20 L
- V_indicat = 100.50 L
- Eroare = (100.50 - 100.20) / 100.20 × 100 = **+0.30%**

## 6. Verificare Conformitate

### 6.1. Limite Admisibile

Fiecare clasă de contor are erori maxime admisibile (EMA) definite conform standardelor metrologice (OIML R49, MID):

| Zona de debit | Interval debit | Eroare Max. Admisibilă |
|---------------|----------------|------------------------|
| Zona inferioară | Q1 ≤ Q < Q2 | ±5% (clasa B) sau ±2% (clasa C) |
| Zona superioară | Q2 ≤ Q ≤ Q3 | ±2% (clasa B) sau ±1% (clasa C) |

### 6.2. Criteriu de Admitere

Pentru fiecare măsurătoare:

```
|Eroare_calculată| ≤ EMA_corespunzătoare_debitului
```

**Rezultat global**:
- **ADMIS**: Toate măsurătorile respectă criteriul de admitere
- **RESPINS**: Cel puțin o măsurătoare depășește eroarea maximă admisibilă

### 6.3. Exemplu de Verificare

Pentru un contor clasa B, DN15:
- Q1 = 15 L/h, Q2 = 30 L/h, Q3 = 300 L/h

Măsurători efectuate:

| Debit | Eroare calculată | EMA | Status |
|-------|------------------|-----|--------|
| 20 L/h (Q1) | +4.2% | ±5% | ✓ ADMIS |
| 25 L/h (Q1-Q2) | +3.8% | ±5% | ✓ ADMIS |
| 50 L/h (Q2) | +1.5% | ±2% | ✓ ADMIS |
| 150 L/h (Q2-Q3) | +0.8% | ±2% | ✓ ADMIS |
| 300 L/h (Q3) | -1.2% | ±2% | ✓ ADMIS |

**Verdict final**: **ADMIS** - toate măsurătorile sunt în limite

## 7. Flux Complet de Calcul

```
INTRARE DATE
    ↓
┌───────────────────────────────────────┐
│ Index_Start, Index_Stop               │
│ + Parametri specifici metodei         │
└───────────────────────────────────────┘
    ↓
┌───────────────────────────────────────┐
│ CALCUL VOLUM REFERINȚĂ                │
│ - Volumetrică: Debitmetru etalon      │
│ - Gravimetrică: Volum corectat cu     │
│   densitatea în funcție de temperatură│
└───────────────────────────────────────┘
    ↓
┌───────────────────────────────────────┐
│ CALCUL VOLUM INDICAT                  │
│ V_indicat = Index_Stop - Index_Start  │
└───────────────────────────────────────┘
    ↓
┌───────────────────────────────────────┐
│ CALCUL EROARE                         │
│ E = (V_ind - V_ref) / V_ref × 100%    │
└───────────────────────────────────────┘
    ↓
┌───────────────────────────────────────┐
│ VERIFICARE LIMITE                     │
│ |E| ≤ EMA ?                           │
└───────────────────────────────────────┘
       Da ↓              ↓ Nu
┌─────────────┐      ┌─────────────┐
│   ADMIS     │      │  RESPINS    │
└─────────────┘      └─────────────┘
```

---

**Document generat pentru**: Aplicație Verificare Contoare de Apă
**Data**: 31.12.2025
**Versiune**: 1.8

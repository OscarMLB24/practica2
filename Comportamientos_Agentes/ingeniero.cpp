#include "ingeniero.hpp"
#include "motorlib/util.h"
#include <iostream>
#include <queue>
#include <set>

using namespace std;

// =========================================================================
// ÁREA DE IMPLEMENTACIÓN DEL ESTUDIANTE
// =========================================================================

Action ComportamientoIngeniero::think(Sensores sensores)
{
  Action accion = IDLE;

  // Decisión del agente según el nivel
  switch (sensores.nivel)
  {
  case 0:
    accion = ComportamientoIngenieroNivel_0(sensores);
    break;
  case 1:
    accion = ComportamientoIngenieroNivel_1(sensores);
    break;
  case 2:
    accion = ComportamientoIngenieroNivel_2(sensores);
    break;
  case 3:
    accion = ComportamientoIngenieroNivel_3(sensores);
    break;
  case 4:
    accion = ComportamientoIngenieroNivel_4(sensores);
    break;
  case 5:
    accion = ComportamientoIngenieroNivel_5(sensores);
    break;
  case 6:
    accion = ComportamientoIngenieroNivel_6(sensores);
    break;
  }

  return accion;
}

///////////////////////////////////////////////////////////////////////////
// Niveles iniciales (Comportamientos reactivos simples)
///////////////////////////////////////////////////////////////////////////

Action ComportamientoIngeniero::ComportamientoIngenieroNivel_0(Sensores sensores)
{
  Action accion = IDLE;

  // El comportamineto de seguir un camino hasta encontrar una planta de T.residuos
  // Poner el valor de los sensores de visión sobre los mapas
  ActualizarMapa(sensores);

  // Actualización de las variables de estado
  if (sensores.superficie[0] == 'D') tiene_zapatillas = true;

  // Definición del comportamiento
  if (sensores.superficie[0] == 'U'){ //Llegué a una 'U'
    return IDLE;
  }

  // Si la última acción fue WALK o JUMP, incrementar la casilla actual como visitada
  if (last_action == WALK || last_action == JUMP) mapaVisitados[sensores.posF][sensores.posC]++; // Marcar la casilla actual como visitada

  // Determinamos la mejor opción entre las casillas
  int pos = 4;
  
  if(!accion_doble) pos = ElegirMovimiento0(sensores);

  switch(pos)
  {
    case 2: // Andar hacia la casilla central (WALK)

      accion = WALK;
      break;

    case 1: // Girar hacia la izquierda (TURN_SL)

      accion = TURN_SL;
      break;

    case 3: // Girar hacia la derecha (TURN_SR)

      accion = TURN_SR;
      break;

    case 4: // Saltar hacia la casilla central de la segundo fila (JUMP)

      accion = JUMP;
      if(accion_doble) accion_doble = false; // Si ya se ha realizado la acción de salto, resetear el flag para la siguiente decisión
      break;

    case 5: // Saltar hacia la casilla diagonal izquierda (TURN_SL + JUMP)

      if(!accion_doble){
        accion = TURN_SL;
        accion_doble = true;
        
      }
      break;

    case 6: // Saltar hacia la casilla diagonal derecha (TURN_SR + JUMP)

      if(!accion_doble){
        accion = TURN_SR;
        accion_doble = true;
      }
      break;

    default:

      accion = TURN_SL; // Si no hay nada interesante, girar a la izquierda por defecto
  }

  // Devolver la siguiente acción a hacer
  last_action = accion;
  
  return accion;
}

///////////////////////////////////////////////////////////////////////////

Action ComportamientoIngeniero::ComportamientoIngenieroNivel_1(Sensores sensores)
{
Action accion = IDLE;

  // El comportamineto de seguir recorriendo el mapa y evitando las casillas más visitadas
  // Poner el valor de los sensores de visión sobre los mapas
  ActualizarMapa(sensores);

  // Actualización de las variables de estado
  if (sensores.superficie[0] == 'D') tiene_zapatillas = true;

  // Si la última acción fue WALK o JUMP, incrementar la casilla actual como visitada
  if (last_action == WALK || last_action == JUMP) mapaVisitados[sensores.posF][sensores.posC]++; // Marcar la casilla actual como visitada

  // Determinamos la mejor opción entre las casillas
  int pos = 4;
  
  if(!accion_doble) pos = ElegirMovimiento1(sensores);

  switch(pos)
  {
    case 2: // Andar hacia la casilla central (WALK)

      accion = WALK;
      break;

    case 1: // Girar hacia la izquierda (TURN_SL)

      accion = TURN_SL;
      break;

    case 3: // Girar hacia la derecha (TURN_SR)

      accion = TURN_SR;
      break;

    case 4: // Saltar hacia la casilla central de la segundo fila (JUMP)

      accion = JUMP;
      if(accion_doble) accion_doble = false; // Si ya se ha realizado la acción de salto, resetear el flag para la siguiente decisión
      break;

    case 5: // Saltar hacia la casilla diagonal izquierda (TURN_SL + JUMP)

      if(!accion_doble){
        accion = TURN_SL;
        accion_doble = true;
        
      }
      break;

    case 6: // Saltar hacia la casilla diagonal derecha (TURN_SR + JUMP)

      if(!accion_doble){
        accion = TURN_SR;
        accion_doble = true;
      }
      break;

    default: // Si no hay nada interesante, girar a la izquierda por defecto

      accion = TURN_SL; 
  }

  // Devolver la siguiente acción a hacer
  last_action = accion;
  
  return accion;
}

///////////////////////////////////////////////////////////////////////////
// Niveles avanzados (Uso de búsqueda)
///////////////////////////////////////////////////////////////////////////

Action ComportamientoIngeniero::ComportamientoIngenieroNivel_2(Sensores sensores)
{
  // TODO: Implementar búsqueda para el Nivel 2.
  return IDLE;
}

///////////////////////////////////////////////////////////////////////////

Action ComportamientoIngeniero::ComportamientoIngenieroNivel_3(Sensores sensores)
{
  return IDLE;
}

///////////////////////////////////////////////////////////////////////////

Action ComportamientoIngeniero::ComportamientoIngenieroNivel_4(Sensores sensores)
{
  return IDLE;
}

///////////////////////////////////////////////////////////////////////////

Action ComportamientoIngeniero::ComportamientoIngenieroNivel_5(Sensores sensores)
{
  return IDLE;
}

///////////////////////////////////////////////////////////////////////////

Action ComportamientoIngeniero::ComportamientoIngenieroNivel_6(Sensores sensores)
{
  return IDLE;
}

// ========================================================================
// FUNCIONES AUXILIARES
// ========================================================================

///////////////////////////////////////////////////////////////////////////
// Nivel 0 y 1: Funciones auxiliares para el comportamiento reactivo
///////////////////////////////////////////////////////////////////////////

int ComportamientoIngeniero::ElegirMovimiento0(Sensores sensores)
{
  // Miramos la superficie de las casillas 
  char i1 = sensores.superficie[1]; // Casilla de la izquierda
  char c1 = sensores.superficie[2]; // Casilla de delante
  char d1 = sensores.superficie[3]; // Casilla de la derecha
  char i2 = sensores.superficie[4]; // Casilla de la izquierda en la segunda fila
  char c2 = sensores.superficie[6]; // Casilla de delante en la segunda fila
  char d2 = sensores.superficie[8]; // Casilla de la derecha en la segunda fila

  if(!es_camino0(i1) && !es_camino0(c1) && !es_camino0(d1) && !es_camino0(i2) && !es_camino0(c2) && !es_camino0(d2)) return 0; // Si no son caminos transitables, no hay nada interesante

  // Comprobamos si las casillas son viables por altura y por personaje, sino marcamos como 'P'
  bool i1_viable = ViablePorAltura(i1, sensores.cota[1] - sensores.cota[0], tiene_zapatillas) && ViablePorPersonaje(i1, sensores.agentes[1]);
  bool c1_viable = ViablePorAltura(c1, sensores.cota[2] - sensores.cota[0], tiene_zapatillas) && ViablePorPersonaje(c1, sensores.agentes[2]);
  bool d1_viable = ViablePorAltura(d1, sensores.cota[3] - sensores.cota[0], tiene_zapatillas) && ViablePorPersonaje(d1, sensores.agentes[3]);
  bool i2_viable = ViablePorAltura(i2, sensores.cota[4] - sensores.cota[0], tiene_zapatillas) && ViablePorPersonaje(i2, sensores.agentes[4]);
  bool c2_viable = ViablePorAltura(c2, sensores.cota[6] - sensores.cota[0], tiene_zapatillas) && ViablePorPersonaje(c2, sensores.agentes[6]);
  bool d2_viable = ViablePorAltura(d2, sensores.cota[8] - sensores.cota[0], tiene_zapatillas) && ViablePorPersonaje(d2, sensores.agentes[8]);

  if(!i1_viable) i1 = 'P';
  if(!c1_viable) c1 = 'P'; 
  if(!d1_viable) d1 = 'P';
  if(!i2_viable) i2 = 'P';
  if(!c2_viable) c2 = 'P';
  if(!d2_viable) d2 = 'P';

  // Calculamos las orientaciones de izquierda y derecha a partir del rumbo actual
  Orientacion or_i  = static_cast<Orientacion>((sensores.rumbo + 7) % 8);
  Orientacion or_d  = static_cast<Orientacion>((sensores.rumbo + 1) % 8);

  // Calculamos las ubicaciones de las casillas de izquierda, centro y derecha
  ubicacion ub_i  = Delante({sensores.posF, sensores.posC, or_i});
  ubicacion ub_c  = Delante({sensores.posF, sensores.posC, sensores.rumbo});
  ubicacion ub_d  = Delante({sensores.posF, sensores.posC, or_d});

  // Calculamos el número de veces que se han visitado las casillas de izquierda, centro y derecha
  int visit_i;
  int visit_c;
  int visit_d;

  // Si la casilla es camino, obtenemos el número de visitas, sino la marcamos como el valor máximo (para que no influya en la decisión)
  if(es_camino0(i1)) visit_i = mapaVisitados[ub_i.f][ub_i.c];
  else visit_i = numeric_limits<int>::max();

  if(es_camino0(c1)) visit_c = mapaVisitados[ub_c.f][ub_c.c];
  else visit_c = numeric_limits<int>::max();

  if(es_camino0(d1)) visit_d = mapaVisitados[ub_d.f][ub_d.c];
  else visit_d = numeric_limits<int>::max();

  // Priorizar casillas 'U'
  if      (c1 == 'U') return 2; 
  else if (i1 == 'U') return 1;
  else if (d1 == 'U') return 3;
  else if (c2 == 'U' && EsViable(c1, sensores.cota[2] - sensores.cota[0], sensores.agentes[2], tiene_zapatillas)) return 4;
  else if (i2 == 'U' && EsViable(i1, sensores.cota[4] - sensores.cota[0], sensores.agentes[4], tiene_zapatillas)) return 5;
  else if (d2 == 'U' && EsViable(d1, sensores.cota[8] - sensores.cota[0], sensores.agentes[8], tiene_zapatillas)) return 6;

  // Si no hay 'U', priorizar 'D' si no se tienen las zapatillas
  if (!tiene_zapatillas){
    if      (c1 == 'D') return 2;
    else if (i1 == 'D') return 1;
    else if (d1 == 'D') return 3;
    else if (c2 == 'D' && EsViable(c1, sensores.cota[2] - sensores.cota[0], sensores.agentes[2], tiene_zapatillas)) return 4;
    else if (i2 == 'D' && EsViable(i1, sensores.cota[4] - sensores.cota[0], sensores.agentes[4], tiene_zapatillas)) return 5;
    else if (d2 == 'D' && EsViable(d1, sensores.cota[8] - sensores.cota[0], sensores.agentes[8], tiene_zapatillas)) return 6;
  }

  // Si no hay 'U' ni 'D', priorizar la casilla menos visitada
  if      (es_camino0(c1) && visit_c <= visit_i && visit_c <= visit_d) return 2;
  else if (es_camino0(i1) && visit_i <= visit_c && visit_i <= visit_d) return 1;
  else if (es_camino0(d1) && visit_d <= visit_c && visit_d <= visit_i) return 3;
  else if (es_camino0(c2) && EsViable(c1, sensores.cota[2] - sensores.cota[0], sensores.agentes[2], tiene_zapatillas)) return 4;
  else if (es_camino0(i2) && EsViable(i1, sensores.cota[4] - sensores.cota[0], sensores.agentes[4], tiene_zapatillas)) return 5;
  else if (es_camino0(d2) && EsViable(d1, sensores.cota[8] - sensores.cota[0], sensores.agentes[8], tiene_zapatillas)) return 6;

  return 0;
}

///////////////////////////////////////////////////////////////////////////

bool ComportamientoIngeniero::es_camino0(unsigned char c) const
{
  return (c == 'C' || c == 'D' || c == 'U');
}

///////////////////////////////////////////////////////////////////////////

bool ComportamientoIngeniero::ViablePorAltura(char casilla, int dif, bool zap)
{
  if (abs(dif) <= 1 or (zap and abs(dif) <= 2)) 
    return true;
  else
    return false;
}

///////////////////////////////////////////////////////////////////////////

bool ComportamientoIngeniero::ViablePorPersonaje(char casilla, char personaje)
{
  if (personaje == '_')
    return true;
  else
    return false;
}

///////////////////////////////////////////////////////////////////////////

bool ComportamientoIngeniero::EsTransitable(char casilla)
{
  return (casilla != 'P' && casilla != 'M' && casilla != 'B');
}

///////////////////////////////////////////////////////////////////////////

bool ComportamientoIngeniero::EsViable(char casilla, int dif, char personaje, bool zap)
{
  return EsTransitable(casilla) && ViablePorAltura(casilla, dif, zap) && ViablePorPersonaje(casilla, personaje);
}

///////////////////////////////////////////////////////////////////////////

int ComportamientoIngeniero::ElegirMovimiento1(Sensores sensores)
{
 // Miramos la superficie de las casillas 
  char i1 = sensores.superficie[1]; // Casilla de la izquierda
  char c1 = sensores.superficie[2]; // Casilla de delante
  char d1 = sensores.superficie[3]; // Casilla de la derecha
  char i2 = sensores.superficie[4]; // Casilla de la izquierda en la segunda fila
  char c2 = sensores.superficie[6]; // Casilla de delante en la segunda fila
  char d2 = sensores.superficie[8]; // Casilla de la derecha en la segunda fila

  if(!es_camino1(i1) && !es_camino1(c1) && !es_camino1(d1) && !es_camino1(i2) && !es_camino1(c2) && !es_camino1(d2)) return 0; // Si no son caminos transitables, no hay nada interesante

  // Comprobamos si las casillas son viables por altura y por personaje, sino marcamos como 'P'
  bool i1_viable = ViablePorAltura(i1, sensores.cota[1] - sensores.cota[0], tiene_zapatillas) && ViablePorPersonaje(i1, sensores.agentes[1]);
  bool c1_viable = ViablePorAltura(c1, sensores.cota[2] - sensores.cota[0], tiene_zapatillas) && ViablePorPersonaje(c1, sensores.agentes[2]);
  bool d1_viable = ViablePorAltura(d1, sensores.cota[3] - sensores.cota[0], tiene_zapatillas) && ViablePorPersonaje(d1, sensores.agentes[3]);
  bool i2_viable = ViablePorAltura(i2, sensores.cota[4] - sensores.cota[0], tiene_zapatillas) && ViablePorPersonaje(i2, sensores.agentes[4]);
  bool c2_viable = ViablePorAltura(c2, sensores.cota[6] - sensores.cota[0], tiene_zapatillas) && ViablePorPersonaje(c2, sensores.agentes[6]);
  bool d2_viable = ViablePorAltura(d2, sensores.cota[8] - sensores.cota[0], tiene_zapatillas) && ViablePorPersonaje(d2, sensores.agentes[8]);

  if(!i1_viable) i1  = 'P';
  if(!c1_viable) c1  = 'P'; 
  if(!d1_viable) d1  = 'P';
  if(!i2_viable) i2 = 'P';
  if(!c2_viable) c2 = 'P';
  if(!d2_viable) d2 = 'P';

  // Calculamos las orientaciones de izquierda y derecha a partir del rumbo actual
  Orientacion or_i = static_cast<Orientacion>((sensores.rumbo + 7) % 8);
  Orientacion or_d = static_cast<Orientacion>((sensores.rumbo + 1) % 8);

  // Calculamos las ubicaciones de las casillas de izquierda, centro y derecha
  ubicacion ub_i = Delante({sensores.posF, sensores.posC, or_i});
  ubicacion ub_c = Delante({sensores.posF, sensores.posC, sensores.rumbo});
  ubicacion ub_d = Delante({sensores.posF, sensores.posC, or_d});

  // Calculamos el número de veces que se han visitado las casillas de izquierda, centro y derecha
  int visit_i;
  int visit_c;
  int visit_d;

  // Si la casilla es camino, obtenemos el número de visitas, sino la marcamos como el valor máximo (para que no influya en la decisión)
  if(es_camino1(i1)) visit_i = mapaVisitados[ub_i.f][ub_i.c];
  else visit_i = numeric_limits<int>::max();

  if(es_camino1(c1)) visit_c = mapaVisitados[ub_c.f][ub_c.c];
  else visit_c = numeric_limits<int>::max();

  if(es_camino1(d1)) visit_d = mapaVisitados[ub_d.f][ub_d.c];
  else visit_d = numeric_limits<int>::max();

  // Prioriar 'X' si la energía es menor de 1000
  if(sensores.energia < 500){
    if      (c1 == 'X') return 2; 
    else if (i1 == 'X') return 1;
    else if (d1 == 'X') return 3;
    else if (c2 == 'X' && EsViable(c1, sensores.cota[2] - sensores.cota[0], sensores.agentes[2], tiene_zapatillas)) return 4;
    else if (i2 == 'X' && EsViable(i1, sensores.cota[4] - sensores.cota[0], sensores.agentes[4], tiene_zapatillas)) return 5;
    else if (d2 == 'X' && EsViable(d1, sensores.cota[8] - sensores.cota[0], sensores.agentes[8], tiene_zapatillas)) return 6;
  }

  // Priorizar 'D' si no se tienen las zapatillas
  if (!tiene_zapatillas){
    if      (c1 == 'D') return 2;
    else if (i1 == 'D') return 1;
    else if (d1 == 'D') return 3;
    else if (c2 == 'D' && EsViable(c1, sensores.cota[2] - sensores.cota[0], sensores.agentes[2], tiene_zapatillas)) return 4;
    else if (i2 == 'D' && EsViable(i1, sensores.cota[4] - sensores.cota[0], sensores.agentes[4], tiene_zapatillas)) return 5;
    else if (d2 == 'D' && EsViable(d1, sensores.cota[8] - sensores.cota[0], sensores.agentes[8], tiene_zapatillas)) return 6;
  }

  // Priorizar la casilla menos visitada entre las opciones viables
  if      (es_camino1(c1) && visit_c <= visit_i && visit_c <= visit_d) return 2;
  else if (es_camino1(i1) && visit_i <= visit_c && visit_i <= visit_d) return 1;
  else if (es_camino1(d1) && visit_d <= visit_i && visit_d <= visit_c) return 3;
  else if (es_camino1(c2) && EsViable(c1, sensores.cota[2] - sensores.cota[0], sensores.agentes[2], tiene_zapatillas)) return 4;
  else if (es_camino1(i2) && EsViable(i1, sensores.cota[4] - sensores.cota[0], sensores.agentes[4], tiene_zapatillas)) return 5;
  else if (es_camino1(d2) && EsViable(d1, sensores.cota[8] - sensores.cota[0], sensores.agentes[8], tiene_zapatillas)) return 6;

  return 0;
}

///////////////////////////////////////////////////////////////////////////

bool ComportamientoIngeniero::es_camino1(unsigned char c) const
{
  return (c == 'C' || c == 'S' || c == 'D' || c == 'U' || c == 'X' /*|| c == 'H' || c == 'A'*/);
}

///////////////////////////////////////////////////////////////////////////

// =========================================================================
// FUNCIONES PROPORCIONADAS
// =========================================================================

/**
 * @brief Actualiza el mapaResultado y mapaCotas con la información de los sensores.
 * @param sensores Datos actuales de los sensores.
 */
void ComportamientoIngeniero::ActualizarMapa(Sensores sensores)
{
  mapaResultado[sensores.posF][sensores.posC] = sensores.superficie[0];
  mapaCotas[sensores.posF][sensores.posC] = sensores.cota[0];

  int pos = 1;
  switch (sensores.rumbo)
  {
  case norte:
    for (int j = 1; j < 4; j++)
      for (int i = -j; i <= j; i++)
      {
        mapaResultado[sensores.posF - j][sensores.posC + i] = sensores.superficie[pos];
        mapaCotas[sensores.posF - j][sensores.posC + i] = sensores.cota[pos++];
      }
    break;
  case noreste:
    mapaResultado[sensores.posF - 1][sensores.posC] = sensores.superficie[1];
    mapaCotas[sensores.posF - 1][sensores.posC] = sensores.cota[1];
    mapaResultado[sensores.posF - 1][sensores.posC + 1] = sensores.superficie[2];
    mapaCotas[sensores.posF - 1][sensores.posC + 1] = sensores.cota[2];
    mapaResultado[sensores.posF][sensores.posC + 1] = sensores.superficie[3];
    mapaCotas[sensores.posF][sensores.posC + 1] = sensores.cota[3];
    mapaResultado[sensores.posF - 2][sensores.posC] = sensores.superficie[4];
    mapaCotas[sensores.posF - 2][sensores.posC] = sensores.cota[4];
    mapaResultado[sensores.posF - 2][sensores.posC + 1] = sensores.superficie[5];
    mapaCotas[sensores.posF - 2][sensores.posC + 1] = sensores.cota[5];
    mapaResultado[sensores.posF - 2][sensores.posC + 2] = sensores.superficie[6];
    mapaCotas[sensores.posF - 2][sensores.posC + 2] = sensores.cota[6];
    mapaResultado[sensores.posF - 1][sensores.posC + 2] = sensores.superficie[7];
    mapaCotas[sensores.posF - 1][sensores.posC + 2] = sensores.cota[7];
    mapaResultado[sensores.posF][sensores.posC + 2] = sensores.superficie[8];
    mapaCotas[sensores.posF][sensores.posC + 2] = sensores.cota[8];
    mapaResultado[sensores.posF - 3][sensores.posC] = sensores.superficie[9];
    mapaCotas[sensores.posF - 3][sensores.posC] = sensores.cota[9];
    mapaResultado[sensores.posF - 3][sensores.posC + 1] = sensores.superficie[10];
    mapaCotas[sensores.posF - 3][sensores.posC + 1] = sensores.cota[10];
    mapaResultado[sensores.posF - 3][sensores.posC + 2] = sensores.superficie[11];
    mapaCotas[sensores.posF - 3][sensores.posC + 2] = sensores.cota[11];
    mapaResultado[sensores.posF - 3][sensores.posC + 3] = sensores.superficie[12];
    mapaCotas[sensores.posF - 3][sensores.posC + 3] = sensores.cota[12];
    mapaResultado[sensores.posF - 2][sensores.posC + 3] = sensores.superficie[13];
    mapaCotas[sensores.posF - 2][sensores.posC + 3] = sensores.cota[13];
    mapaResultado[sensores.posF - 1][sensores.posC + 3] = sensores.superficie[14];
    mapaCotas[sensores.posF - 1][sensores.posC + 3] = sensores.cota[14];
    mapaResultado[sensores.posF][sensores.posC + 3] = sensores.superficie[15];
    mapaCotas[sensores.posF][sensores.posC + 3] = sensores.cota[15];
    break;
  case este:
    for (int j = 1; j < 4; j++)
      for (int i = -j; i <= j; i++)
      {
        mapaResultado[sensores.posF + i][sensores.posC + j] = sensores.superficie[pos];
        mapaCotas[sensores.posF + i][sensores.posC + j] = sensores.cota[pos++];
      }
    break;
  case sureste:
    mapaResultado[sensores.posF][sensores.posC + 1] = sensores.superficie[1];
    mapaCotas[sensores.posF][sensores.posC + 1] = sensores.cota[1];
    mapaResultado[sensores.posF + 1][sensores.posC + 1] = sensores.superficie[2];
    mapaCotas[sensores.posF + 1][sensores.posC + 1] = sensores.cota[2];
    mapaResultado[sensores.posF + 1][sensores.posC] = sensores.superficie[3];
    mapaCotas[sensores.posF + 1][sensores.posC] = sensores.cota[3];
    mapaResultado[sensores.posF][sensores.posC + 2] = sensores.superficie[4];
    mapaCotas[sensores.posF][sensores.posC + 2] = sensores.cota[4];
    mapaResultado[sensores.posF + 1][sensores.posC + 2] = sensores.superficie[5];
    mapaCotas[sensores.posF + 1][sensores.posC + 2] = sensores.cota[5];
    mapaResultado[sensores.posF + 2][sensores.posC + 2] = sensores.superficie[6];
    mapaCotas[sensores.posF + 2][sensores.posC + 2] = sensores.cota[6];
    mapaResultado[sensores.posF + 2][sensores.posC + 1] = sensores.superficie[7];
    mapaCotas[sensores.posF + 2][sensores.posC + 1] = sensores.cota[7];
    mapaResultado[sensores.posF + 2][sensores.posC] = sensores.superficie[8];
    mapaCotas[sensores.posF + 2][sensores.posC] = sensores.cota[8];
    mapaResultado[sensores.posF][sensores.posC + 3] = sensores.superficie[9];
    mapaCotas[sensores.posF][sensores.posC + 3] = sensores.cota[9];
    mapaResultado[sensores.posF + 1][sensores.posC + 3] = sensores.superficie[10];
    mapaCotas[sensores.posF + 1][sensores.posC + 3] = sensores.cota[10];
    mapaResultado[sensores.posF + 2][sensores.posC + 3] = sensores.superficie[11];
    mapaCotas[sensores.posF + 2][sensores.posC + 3] = sensores.cota[11];
    mapaResultado[sensores.posF + 3][sensores.posC + 3] = sensores.superficie[12];
    mapaCotas[sensores.posF + 3][sensores.posC + 3] = sensores.cota[12];
    mapaResultado[sensores.posF + 3][sensores.posC + 2] = sensores.superficie[13];
    mapaCotas[sensores.posF + 3][sensores.posC + 2] = sensores.cota[13];
    mapaResultado[sensores.posF + 3][sensores.posC + 1] = sensores.superficie[14];
    mapaCotas[sensores.posF + 3][sensores.posC + 1] = sensores.cota[14];
    mapaResultado[sensores.posF + 3][sensores.posC] = sensores.superficie[15];
    mapaCotas[sensores.posF + 3][sensores.posC] = sensores.cota[15];
    break;
  case sur:
    for (int j = 1; j < 4; j++)
      for (int i = -j; i <= j; i++)
      {
        mapaResultado[sensores.posF + j][sensores.posC - i] = sensores.superficie[pos];
        mapaCotas[sensores.posF + j][sensores.posC - i] = sensores.cota[pos++];
      }
    break;
  case suroeste:
    mapaResultado[sensores.posF + 1][sensores.posC] = sensores.superficie[1];
    mapaCotas[sensores.posF + 1][sensores.posC] = sensores.cota[1];
    mapaResultado[sensores.posF + 1][sensores.posC - 1] = sensores.superficie[2];
    mapaCotas[sensores.posF + 1][sensores.posC - 1] = sensores.cota[2];
    mapaResultado[sensores.posF][sensores.posC - 1] = sensores.superficie[3];
    mapaCotas[sensores.posF][sensores.posC - 1] = sensores.cota[3];
    mapaResultado[sensores.posF + 2][sensores.posC] = sensores.superficie[4];
    mapaCotas[sensores.posF + 2][sensores.posC] = sensores.cota[4];
    mapaResultado[sensores.posF + 2][sensores.posC - 1] = sensores.superficie[5];
    mapaCotas[sensores.posF + 2][sensores.posC - 1] = sensores.cota[5];
    mapaResultado[sensores.posF + 2][sensores.posC - 2] = sensores.superficie[6];
    mapaCotas[sensores.posF + 2][sensores.posC - 2] = sensores.cota[6];
    mapaResultado[sensores.posF + 1][sensores.posC - 2] = sensores.superficie[7];
    mapaCotas[sensores.posF + 1][sensores.posC - 2] = sensores.cota[7];
    mapaResultado[sensores.posF][sensores.posC - 2] = sensores.superficie[8];
    mapaCotas[sensores.posF][sensores.posC - 2] = sensores.cota[8];
    mapaResultado[sensores.posF + 3][sensores.posC] = sensores.superficie[9];
    mapaCotas[sensores.posF + 3][sensores.posC] = sensores.cota[9];
    mapaResultado[sensores.posF + 3][sensores.posC - 1] = sensores.superficie[10];
    mapaCotas[sensores.posF + 3][sensores.posC - 1] = sensores.cota[10];
    mapaResultado[sensores.posF + 3][sensores.posC - 2] = sensores.superficie[11];
    mapaCotas[sensores.posF + 3][sensores.posC - 2] = sensores.cota[11];
    mapaResultado[sensores.posF + 3][sensores.posC - 3] = sensores.superficie[12];
    mapaCotas[sensores.posF + 3][sensores.posC - 3] = sensores.cota[12];
    mapaResultado[sensores.posF + 2][sensores.posC - 3] = sensores.superficie[13];
    mapaCotas[sensores.posF + 2][sensores.posC - 3] = sensores.cota[13];
    mapaResultado[sensores.posF + 1][sensores.posC - 3] = sensores.superficie[14];
    mapaCotas[sensores.posF + 1][sensores.posC - 3] = sensores.cota[14];
    mapaResultado[sensores.posF][sensores.posC - 3] = sensores.superficie[15];
    mapaCotas[sensores.posF][sensores.posC - 3] = sensores.cota[15];
    break;
  case oeste:
    for (int j = 1; j < 4; j++)
      for (int i = -j; i <= j; i++)
      {
        mapaResultado[sensores.posF - i][sensores.posC - j] = sensores.superficie[pos];
        mapaCotas[sensores.posF - i][sensores.posC - j] = sensores.cota[pos++];
      }
    break;
  case noroeste:
    mapaResultado[sensores.posF][sensores.posC - 1] = sensores.superficie[1];
    mapaCotas[sensores.posF][sensores.posC - 1] = sensores.cota[1];
    mapaResultado[sensores.posF - 1][sensores.posC - 1] = sensores.superficie[2];
    mapaCotas[sensores.posF - 1][sensores.posC - 1] = sensores.cota[2];
    mapaResultado[sensores.posF - 1][sensores.posC] = sensores.superficie[3];
    mapaCotas[sensores.posF - 1][sensores.posC] = sensores.cota[3];
    mapaResultado[sensores.posF][sensores.posC - 2] = sensores.superficie[4];
    mapaCotas[sensores.posF][sensores.posC - 2] = sensores.cota[4];
    mapaResultado[sensores.posF - 1][sensores.posC - 2] = sensores.superficie[5];
    mapaCotas[sensores.posF - 1][sensores.posC - 2] = sensores.cota[5];
    mapaResultado[sensores.posF - 2][sensores.posC - 2] = sensores.superficie[6];
    mapaCotas[sensores.posF - 2][sensores.posC - 2] = sensores.cota[6];
    mapaResultado[sensores.posF - 2][sensores.posC - 1] = sensores.superficie[7];
    mapaCotas[sensores.posF - 2][sensores.posC - 1] = sensores.cota[7];
    mapaResultado[sensores.posF - 2][sensores.posC] = sensores.superficie[8];
    mapaCotas[sensores.posF - 2][sensores.posC] = sensores.cota[8];
    mapaResultado[sensores.posF][sensores.posC - 3] = sensores.superficie[9];
    mapaCotas[sensores.posF][sensores.posC - 3] = sensores.cota[9];
    mapaResultado[sensores.posF - 1][sensores.posC - 3] = sensores.superficie[10];
    mapaCotas[sensores.posF - 1][sensores.posC - 3] = sensores.cota[10];
    mapaResultado[sensores.posF - 2][sensores.posC - 3] = sensores.superficie[11];
    mapaCotas[sensores.posF - 2][sensores.posC - 3] = sensores.cota[11];
    mapaResultado[sensores.posF - 3][sensores.posC - 3] = sensores.superficie[12];
    mapaCotas[sensores.posF - 3][sensores.posC - 3] = sensores.cota[12];
    mapaResultado[sensores.posF - 3][sensores.posC - 2] = sensores.superficie[13];
    mapaCotas[sensores.posF - 3][sensores.posC - 2] = sensores.cota[13];
    mapaResultado[sensores.posF - 3][sensores.posC - 1] = sensores.superficie[14];
    mapaCotas[sensores.posF - 3][sensores.posC - 1] = sensores.cota[14];
    mapaResultado[sensores.posF - 3][sensores.posC] = sensores.superficie[15];
    mapaCotas[sensores.posF - 3][sensores.posC] = sensores.cota[15];
    break;
  }
}

/**
 * @brief Determina si una casilla es transitable para el ingeniero.
 * @param f Fila de la casilla.
 * @param c Columna de la casilla.
 * @param tieneZapatillas Indica si el agente posee las zapatillas.
 * @return true si la casilla es transitable (no es muro ni precipicio).
 */
bool ComportamientoIngeniero::EsCasillaTransitableLevel0(int f, int c, bool tieneZapatillas)
{
  if (f < 0 || f >= mapaResultado.size() || c < 0 || c >= mapaResultado[0].size())
    return false;
  return es_camino0(mapaResultado[f][c]); // Solo 'C', 'D', 'U' son transitables en Nivel 0
}

/**
 * @brief Comprueba si la casilla de delante es accesible por diferencia de altura.
 * Para el ingeniero: desnivel máximo 1 sin zapatillas, 2 con zapatillas.
 * @param actual Estado actual del agente (fila, columna, orientacion, zap).
 * @return true si el desnivel con la casilla de delante es admisible.
 */
bool ComportamientoIngeniero::EsAccesiblePorAltura(const ubicacion &actual, bool zap)
{
  ubicacion del = Delante(actual);
  if (del.f < 0 || del.f >= mapaCotas.size() || del.c < 0 || del.c >= mapaCotas[0].size())
    return false;
  int desnivel = abs(mapaCotas[del.f][del.c] - mapaCotas[actual.f][actual.c]);
  if (zap && desnivel > 2)
    return false;
  if (!zap && desnivel > 1)
    return false;
  return true;
}

/**
 * @brief Devuelve la posición (fila, columna) de la casilla que hay delante del agente.
 * Calcula la casilla frontal según la orientación actual (8 direcciones).
 * @param actual Estado actual del agente (fila, columna, orientacion).
 * @return Estado con la fila y columna de la casilla de enfrente.
 */
ubicacion ComportamientoIngeniero::Delante(const ubicacion &actual) const
{
  ubicacion delante = actual;
  switch (actual.brujula)
  {
  case 0:
    delante.f--;
    break; // norte
  case 1:
    delante.f--;
    delante.c++;
    break; // noreste
  case 2:
    delante.c++;
    break; // este
  case 3:
    delante.f++;
    delante.c++;
    break; // sureste
  case 4:
    delante.f++;
    break; // sur
  case 5:
    delante.f++;
    delante.c--;
    break; // suroeste
  case 6:
    delante.c--;
    break; // oeste
  case 7:
    delante.f--;
    delante.c--;
    break; // noroeste
  }
  return delante;
}

/**
 * @brief Imprime por consola la secuencia de acciones de un plan.
 *
 * @param plan  Lista de acciones del plan.
 */
void ComportamientoIngeniero::PintaPlan(const list<Action> &plan)
{
  auto it = plan.begin();
  while (it != plan.end())
  {
    if (*it == WALK)
    {
      cout << "W ";
    }
    else if (*it == JUMP)
    {
      cout << "J ";
    }
    else if (*it == TURN_SR)
    {
      cout << "r ";
    }
    else if (*it == TURN_SL)
    {
      cout << "l ";
    }
    else if (*it == COME)
    {
      cout << "C ";
    }
    else if (*it == IDLE)
    {
      cout << "I ";
    }
    else
    {
      cout << "-_ ";
    }
    it++;
  }
  cout << "( longitud " << plan.size() << ")" << endl;
}

/**
 * @brief Imprime las coordenadas y operaciones de un plan de tubería.
 *
 * @param plan  Lista de pasos (fila, columna, operación),
 *              donde operacion = -1 (DIG), operación = 1 (RAISE).
 */
void ComportamientoIngeniero::PintaPlan(const list<Paso> &plan)
{
  auto it = plan.begin();
  while (it != plan.end())
  {
    cout << it->fil << ", " << it->col << " (" << it->op << ")\n";
    it++;
  }
  cout << "( longitud " << plan.size() << ")" << endl;
}

/**
 * @brief Convierte un plan de acciones en una lista de casillas para
 *        su visualización en el mapa 2D.
 *
 * @param st    Estado de partida.
 * @param plan  Lista de acciones del plan.
 */
void ComportamientoIngeniero::VisualizaPlan(const ubicacion &st,
                                            const list<Action> &plan)
{
  listaPlanCasillas.clear();
  ubicacion cst = st;

  listaPlanCasillas.push_back({cst.f, cst.c, WALK});
  auto it = plan.begin();
  while (it != plan.end())
  {

    switch (*it)
    {
    case JUMP:
      switch (cst.brujula)
      {
      case 0:
        cst.f--;
        break;
      case 1:
        cst.f--;
        cst.c++;
        break;
      case 2:
        cst.c++;
        break;
      case 3:
        cst.f++;
        cst.c++;
        break;
      case 4:
        cst.f++;
        break;
      case 5:
        cst.f++;
        cst.c--;
        break;
      case 6:
        cst.c--;
        break;
      case 7:
        cst.f--;
        cst.c--;
        break;
      }
      if (cst.f >= 0 && cst.f < mapaResultado.size() &&
          cst.c >= 0 && cst.c < mapaResultado[0].size())
        listaPlanCasillas.push_back({cst.f, cst.c, JUMP});
    case WALK:
      switch (cst.brujula)
      {
      case 0:
        cst.f--;
        break;
      case 1:
        cst.f--;
        cst.c++;
        break;
      case 2:
        cst.c++;
        break;
      case 3:
        cst.f++;
        cst.c++;
        break;
      case 4:
        cst.f++;
        break;
      case 5:
        cst.f++;
        cst.c--;
        break;
      case 6:
        cst.c--;
        break;
      case 7:
        cst.f--;
        cst.c--;
        break;
      }
      if (cst.f >= 0 && cst.f < mapaResultado.size() &&
          cst.c >= 0 && cst.c < mapaResultado[0].size())
        listaPlanCasillas.push_back({cst.f, cst.c, WALK});
      break;
    case TURN_SR:
      cst.brujula = (Orientacion) (( (int) cst.brujula + 1) % 8);
      break;
    case TURN_SL:
      cst.brujula = (Orientacion) (( (int) cst.brujula + 7) % 8);
      break;
    }
    it++;
  }
}

/**
 * @brief Convierte un plan de tubería en la lista de casillas usada
 *        por el sistema de visualización.
 *
 * @param st    Estado de partida (no utilizado directamente).
 * @param plan  Lista de pasos del plan de tubería.
 */
void ComportamientoIngeniero::VisualizaRedTuberias(const list<Paso> &plan)
{
  listaCanalizacionTuberias.clear();
  auto it = plan.begin();
  while (it != plan.end())
  {
    listaCanalizacionTuberias.push_back({it->fil, it->col, it->op});
    it++;
  }
}
#ifndef COMPORTAMIENTOINGENIERO_H
#define COMPORTAMIENTOINGENIERO_H

#include <chrono>
#include <list>
#include <map>
#include <set>
#include <thread>
#include <time.h>

#include "comportamientos/comportamiento.hpp"

class ComportamientoIngeniero : public Comportamiento {
public:
  // =========================================================================
  // CONSTRUCTORES
  // =========================================================================
  
  /**
   * @brief Constructor para niveles 0, 1 y 6 (sin mapa completo)
   * @param size Tamaño del mapa (si es 0, se inicializa más tarde)
   */
  ComportamientoIngeniero(unsigned int size = 0) : Comportamiento(size) {
   
    // Inicializar Variables de Estado
    last_action = IDLE;
    tiene_zapatillas = false;
    accion_doble = false;

    // Inicializar el mapa de visitados con ceros
    mapaVisitados = vector<vector<unsigned int>>(mapaResultado.size(), vector<unsigned int>(mapaResultado[0].size(), 0));
  }

  /**
   * @brief Constructor para niveles 2, 3, 4 y 5 (con mapa completo conocido)
   * @param mapaR Mapa de terreno conocido
   * @param mapaC Mapa de cotas conocido
   */
  ComportamientoIngeniero(std::vector<std::vector<unsigned char>> mapaR, 
                         std::vector<std::vector<unsigned char>> mapaC): 
                         Comportamiento(mapaR, mapaC) {
    
    // Inicializar Variables de Estado

  }

  ComportamientoIngeniero(const ComportamientoIngeniero &comport)
      : Comportamiento(comport) {}
  ~ComportamientoIngeniero() {}

  /**
   * @brief Bucle principal de decisión del agente.
   * Estudia los sensores y decide la siguiente acción.
   * 
   * EJEMPLO DE USO:
   * Action accion = think(sensores);
   * return accion; // El motor ejecutará esta acción
   */
  Action think(Sensores sensores);

  ComportamientoIngeniero *clone() {
    return new ComportamientoIngeniero(*this);
  }

  // =========================================================================
  // ÁREA DE IMPLEMENTACIÓN DEL ESTUDIANTE
  // =========================================================================

  // Funciones específicas para cada nivel (para ser implementadas por el alumno)
  /**
   * @brief Implementación del Nivel 0.
   * @param sensores Datos actuales de los sensores del agente.
   * @return Acción a realizar.
   */

  Action ComportamientoIngenieroNivel_0(Sensores sensores);
  
  /**
   * @brief Implementación del Nivel 1.
   * @param sensores Datos actuales de los sensores del agente.
   * @return Acción a realizar.
   */
  Action ComportamientoIngenieroNivel_1(Sensores sensores);
  
  /**
   * @brief Implementación del Nivel 2.
   * @param sensores Datos actuales de los sensores del agente.
   * @return Acción a realizar.
   */ 
  Action ComportamientoIngenieroNivel_2(Sensores sensores);
  
  /**
   * @brief Implementación del Nivel 3.
   * @param sensores Datos actuales de los sensores del agente.
   * @return Acción a realizar.
   */
  Action ComportamientoIngenieroNivel_3(Sensores sensores);
  
  /**
   * @brief Implementación del Nivel 4.
   * @param sensores Datos actuales de los sensores del agente.
   * @return Acción a realizar.
   */
  Action ComportamientoIngenieroNivel_4(Sensores sensores);
  
  /**
   * @brief Implementación del Nivel 5.
   * @param sensores Datos actuales de los sensores del agente.
   * @return Acción a realizar.
   */
  Action ComportamientoIngenieroNivel_5(Sensores sensores);
  
  /**
   * @brief Implementación del Nivel 6.
   * @param sensores Datos actuales de los sensores del agente.
   * @return Acción a realizar.
   */
  Action ComportamientoIngenieroNivel_6(Sensores sensores);

  /**
   * @brief Determina la mejor opción entre las 3 casillas que tiene delante para el Nivel 0.
   * @param i terreno que hay en la posición 1 de superficie (45 izq).
   * @param c terreno que hay en la posición 2 de superficie (justo delante).
   * @param d terreno que hay en la posición 3 de superficie (45 der).
   * @param zap indica si estoy en posesion de las zapatillas.
   * @return 2 si es mejor WALK, 1 para TURN_SL, 3 para TURN_SR, 4 para JUMP, 5 para TURN_SL + JUMP, 6 para TURN_SR + JUMP. 0 no hay nada interesante.   */
  int ElegirMovimiento0(Sensores sensores);

  /*
  * @brief Determina si la casilla es un camino para el Nivel 0.
  * @param c tipo de terreno.
  * @return true si la casilla es un camino, false si no lo es.
  */
  bool es_camino0(unsigned char c) const;

  /**
   * @brief Determina si la casilla es viable por altura.
   * @param casilla tipo de terreno.
   * @param dif diferencia de altura entre casillas.
   * @param zap indica si estoy en posesion de las zapatillas.
   * @return True si la casilla es viable por altura, false si no lo es
   */
  bool ViablePorAltura(char casilla, int dif, bool zap);
  
  /**
   * @brief Determina si la casilla es viable por personaje (si hay otro agente en la casilla, no es viable).
   * @param casilla tipo de personaje en la casilla.
   * @return True si la casilla es viable por personaje, false si no lo es
   */
  bool ViablePorPersonaje(char casilla, char personaje);

  /**
   * @brief Determina si una casilla es transitable (no es muro ni precipicio ni bosque).
   * @param casilla tipo de terreno en la casilla.
   * @return true si la casilla es transitable, false si es un obstáculo
   */
  bool EsTransitable(char casilla);

  /**
   * @brief Determina si una casilla es viable teniendo en cuenta altura, personaje y transitabilidad.
   * @param casilla tipo de terreno en la casilla.
   * @param dif diferencia de altura entre casillas.
   * @param personaje tipo de personaje en la casilla.
   * @param zap indica si estoy en posesion de las zapatillas.
   * @return True si la casilla es viable, false si no lo es
   */
  bool EsViable(char casilla, int dif, char personaje, bool zap);

  /**
   * @brief Determina la mejor opción entre las 3 casillas que tiene delante para el Nivel 1.
   * @param i terreno que hay en la posición 1 de superficie (45 izq).
   * @param c terreno que hay en la posición 2 de superficie (justo delante).
   * @param d terreno que hay en la posición 3 de superficie (45 der).
   * @param zap indica si estoy en posesion de las zapatillas.
   * @return 2 si es mejor WALK, 1 para TURN_SL, 3 para TURN_SR, 4 para JUMP, 5 para TURN_SL + JUMP, 6 para TURN_SR + JUMP. 0 no hay nada interesante.
   */
  int ElegirMovimiento1(Sensores sensores);

  /*
  * @brief Determina si la casilla es un camino para el Nivel 1.
  * @param c tipo de terreno.
  * @return true si la casilla es un camino, false si no lo es.
  */
  bool es_camino1(unsigned char c) const;

protected:
  // =========================================================================
  // FUNCIONES PROPORCIONADAS
  // =========================================================================

  /**
   * @brief Actualiza la información del mapa interno basándose en los sensores.
   * IMPORTANTE: Esta función ya está implementada. Actualiza mapaResultado y mapaCotas
   * con la información de los 16 sensores (casilla actual + 15 casillas alrededor).
   */
  void ActualizarMapa(Sensores sensores);

  /**
   * @brief Comprueba si una casilla es transitable.
   * @param f Fila de la casilla.
   * @param c Columna de la casilla.
   * @param tieneZapatillas Indica si el agente posee zapatillas.
   * @return true si la casilla es transitable (no es muro ni precipicio).
   */
  bool EsCasillaTransitableLevel0(int f, int c, bool tieneZapatillas);

  /**
   * @brief Comprueba si la casilla de delante es accesible por diferencia de altura.
   * REGLAS: Desnivel máximo 1 sin zapatillas, 2 con zapatillas.
   * @param actual Estado actual del agente (fila, columna, orientacion).
   * @return true si el desnivel con la casilla de delante es admisible.
   */
  bool EsAccesiblePorAltura(const ubicacion &actual, bool zap);

  /**
   * @brief Devuelve la posición (fila, columna) de la casilla que hay delante del agente.
   * @param actual Estado actual del agente (fila, columna, orientacion).
   * @return Estado con la fila y columna de la casilla de enfrente.
   */
  ubicacion Delante(const ubicacion &actual) const;

  /**
 * @brief Imprime por consola la secuencia de acciones de un plan para un agente.
 * @param plan  Lista de acciones del plan.
 */
  void PintaPlan(const list<Action> &plan);


/**
 * @brief Imprime las coordenadas y operaciones de un plan de tubería.
 * @param plan  Lista de pasos (fila, columna, operación).
 */
  void PintaPlan(const list<Paso> &plan);

  /**
 * @brief Convierte un plan de acciones en una lista de casillas para
 *        su visualización en el mapa gráfico.
 * @param st    Estado de partida.
 * @param plan  Lista de acciones del plan.
 */
  void VisualizaPlan(const ubicacion &st, const list<Action> &plan);

  /**
 * @brief Convierte un plan de tubería en la lista de casillas usada
 *        por el sistema de visualización.
 * @param st    Estado de partida (no utilizado directamente).
 * @param plan  Lista de pasos del plan de tubería.
 */
  void VisualizaRedTuberias(const list<Paso> &plan);

private:
  // =========================================================================
  // VARIABLES DE ESTADO (PUEDEN SER EXTENDIDAS POR EL ALUMNO)
  // =========================================================================
 
  Action last_action;     // Almacena la última acción ejecutada
  bool tiene_zapatillas;  // Indica si el agente tiene las zapatillas 
  vector<vector<unsigned int>> mapaVisitados; // Mapa para marcar las casillas visitadas (opcional, puede ser útil para eviter ciclos)
  bool accion_doble;      // Indica si se quiere realizar un salto hacia una casilla diagonal (en cuyo caso se necesita realizar dos acciones: girar y luego caminar)
};

#endif

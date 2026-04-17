#ifndef COMPORTAMIENTOTECNICO_H
#define COMPORTAMIENTOTECNICO_H

#include <chrono>
#include <time.h>
#include <thread>
#include <list>

#include "comportamientos/comportamiento.hpp"

// =========================================================================
// DOCUMENTACIÓN PARA ESTUDIANTES
// =========================================================================
/*
 * CLASE: ComportamientoTecnico
 * 
 * DESCRIPCIÓN:
 * Esta clase implementa el comportamiento del agente Técnico en el mundo Belkan.
 * El técnico colabora con el ingeniero para resolver el problema de instalación de tuberías
 */

class ComportamientoTecnico : public Comportamiento {
public:
  // =========================================================================
  // CONSTRUCTORES
  // =========================================================================
  
  /**
   * @brief Constructor para niveles 0, 1 y 6 (sin mapa completo)
   * @param size Tamaño del mapa (si es 0, se inicializa más tarde)
   */
  ComportamientoTecnico(unsigned int size = 0) : Comportamiento(size) {
    
    // Inicializar Variables de Estado
    last_action = IDLE;
    tiene_zapatillas = false;

    // Inicializar el mapa de visitados con ceros
    mapaVisitados = vector<vector<unsigned int>>(mapaResultado.size(), vector<unsigned int>(mapaResultado[0].size(), 0));
  }

  /**
   * @brief Constructor para niveles 2, 3, 4 y 5 (con mapa completo conocido)
   * @param mapaR Mapa de terreno conocido
   * @param mapaC Mapa de cotas conocido
   */
  ComportamientoTecnico(std::vector<std::vector<unsigned char>> mapaR, 
                       std::vector<std::vector<unsigned char>> mapaC): 
                       Comportamiento(mapaR, mapaC) {
    
    // Inicializar Variables de Estado

  }

  ComportamientoTecnico(const ComportamientoTecnico &comport): Comportamiento(comport) {}
  ~ComportamientoTecnico() {}

  /**
   * @brief Bucle principal de decisión del técnico.
   * Estudia los sensores y decide la siguiente acción.
   * 
   * EJEMPLO DE USO:
   * Action accion = think(sensores);
   * return accion; // El motor ejecutará esta acción
   */
  Action think(Sensores sensores);

  ComportamientoTecnico *clone() {
    return new ComportamientoTecnico(*this);
  }

  // =========================================================================
  // ÁREA DE IMPLEMENTACIÓN DEL ESTUDIANTE
  // =========================================================================

/**
 * @brief Comportamiento del técnico para el Nivel 0.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
  Action ComportamientoTecnicoNivel_0(Sensores sensores);
  
/**
 * @brief Comportamiento del técnico para el Nivel 1.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
  Action ComportamientoTecnicoNivel_1(Sensores sensores);
  
/**
 * @brief Comportamiento del técnico para el Nivel 2.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
  Action ComportamientoTecnicoNivel_2(Sensores sensores);
  
/**
 * @brief Comportamiento del técnico para el Nivel 3.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
  Action ComportamientoTecnicoNivel_3(Sensores sensores);
  
/**
 * @brief Comportamiento del técnico para el Nivel 4.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
  Action ComportamientoTecnicoNivel_4(Sensores sensores);
  
/**
 * @brief Comportamiento del técnico para el Nivel 5.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
  Action ComportamientoTecnicoNivel_5(Sensores sensores);
  
/**
 * @brief Comportamiento del técnico para el Nivel 6.
 * @param sensores Datos actuales de los sensores.
 * @return Acción a realizar.
 */
  Action ComportamientoTecnicoNivel_6(Sensores sensores);

/**
 * @brief Determina la mejor opción entre las 3 casillas que tiene delante
 * @param i terreno que hay en la posición 1 de superficie (45 izq)
 * @param c terreno que hay en la posición 2 de superficie (justo delante)
 * @param d terreno que hay en la posición 3 de superficie (45 der)
 * @return 2 si es mejor WALK, 1 para TURN_SL y 3 para TURN_SR. 0 no hay nada interesante
 */
  int ElegirMovimiento0(Sensores sensores);

/**
  * @brief Determina si la casilla es un camino para el Nivel 0.
  * @param c tipo de terreno.
  * @return true si la casilla es un camino, false si no lo es.
  */
  bool es_camino0(unsigned char c) const;

/**
 * @brief Determina si la casilla es viable por altura
 * @param casilla tipo de terreno
 * @param dif diferencia de altura entre casillas
 * @param zap indica si estoy en posesion de las zapatillas
 * @return True si la casilla es viable por altura, false si no lo es
  */
  bool ViablePorAltura(char casilla, int dif, bool zap);

  /**
   * @brief Determina si la casilla es viable por personaje (si hay otro agente en la casilla, no es viable)
   * @param casilla tipo de personaje en la casilla
   * True si la casilla es viable por personaje, false si no lo es
   */
  bool ViablePorPersonaje(char casilla, char personaje);

  /**
   * @brief Determina la mejor opción entre las 3 casillas que tiene delante para el Nivel 1.
   * @param i terreno que hay en la posición 1 de superficie (45 izq).
   * @param c terreno que hay en la posición 2 de superficie (justo delante).
   * @param d terreno que hay en la posición 3 de superficie (45 der).
   * @return 2 si es mejor WALK, 1 para TURN_SL y 3 para TURN_SR. 0 no hay nada interesante.
   */
  int ElegirMovimiento1(Sensores sensores);

  /*
  * @brief Determina si la casilla es un camino para el Nivel 1.
  * @param c tipo de terreno.
  * @return true si la casilla es un camino, false si no lo es.
  */
  bool es_camino1(unsigned char c, bool zap) const;

protected:
  // =========================================================================
  // FUNCIONES PROPORCIONADAS
  // =========================================================================

  /**
   * @brief Actualiza el mapaResultado y mapaCotas con la información de los sensores.
   * IMPORTANTE: Esta función ya está implementada. Actualiza mapaResultado y mapaCotas
   * con la información de los 16 sensores.
   */
  void ActualizarMapa(Sensores sensores);

  /**
   * @brief Determina si una casilla es transitable para el técnico.
   * NOTA: El técnico puede tener reglas de transitabilidad diferentes al ingeniero.
   * @param f Fila de la casilla.
   * @param c Columna de la casilla.
   * @param tieneZapatillas Indica si el agente posee las zapatillas.
   * @return true si la casilla es transitable.
   */
  bool EsCasillaTransitableLevel0(int f, int c, bool tieneZapatillas);

  /**
   * @brief Comprueba si la casilla de delante es accesible por diferencia de altura.
   * REGLA PARA TÉCNICO: Desnivel máximo siempre 1 (independiente de zapatillas).
   * @param actual Estado actual del agente (fila, columna, orientacion).
   * @return true si el desnivel con la casilla de delante es admisible.
   */
  bool EsAccesiblePorAltura(const ubicacion &actual);

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

private:
  // =========================================================================
  // VARIABLES DE ESTADO (PUEDEN SER EXTENDIDAS POR EL ALUMNO)
  // =========================================================================

  Action last_action;     // Almacena la última acción ejecutada
  bool tiene_zapatillas;  // Indica si el agente tiene las zapatillas 
  vector<vector<unsigned int>> mapaVisitados; // Mapa para marcar las casillas visitadas (opcional, puede ser útil para eviter ciclos)
};

#endif

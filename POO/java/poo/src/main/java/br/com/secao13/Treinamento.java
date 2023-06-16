
package br.com.secao13;

/**
 *
 * @author silas
 */
public abstract class Treinamento {
    
    final void treinoDiario(){
        preparoFisico();
        jogoTreino();
        treinoTatico();      
    }
    
    public abstract void preparoFisico();
    
    public abstract void jogoTreino();
    
    public final void treinoTatico(){
        System.out.println("Treino tático....");
    }
    
    
}

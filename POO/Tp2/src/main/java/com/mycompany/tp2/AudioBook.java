
package com.mycompany.tp2;

import java.util.ArrayList;

/**
 *
 * @author silas
 */
public class AudioBook extends Livro {
    private float duracao;
    private String formatoAudio;

    public AudioBook(float duracao,String formatoAudio,ArrayList escritores,String titulo, ArrayList capitulos, int anoPublicacao, String idiomaOriginal, ArrayList keywords){
        super(escritores,titulo,capitulos,anoPublicacao,idiomaOriginal,keywords);
        this.duracao = duracao;
        this.formatoAudio = formatoAudio;
    }
    
    public float getDuracao() {
        return duracao;
    }

    public void setDuracao(float duracao) {
        this.duracao = duracao;
    }

    public String getFormatoAudio() {
        return formatoAudio;
    }

    public void setFormatoAudio(String formatoAudio) {
        this.formatoAudio = formatoAudio;
    }
    
    
}

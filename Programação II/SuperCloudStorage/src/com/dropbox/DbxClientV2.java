package com.dropbox;

import java.io.File;
import java.io.InputStream;

public class DbxClientV2 {
    
    public void uploadAndFinish(InputStream stream)
    {
        System.out.println("fazendo upload para dropbox");
    }
    
    public File downloadAndFinish(String fileName)
    {
        System.out.println("fazendo download de " + fileName + " para dropbox");
        return null;
    }
    
    public String[] files()
    {
        String[] files = {"teste dbx.txt", "imagem dbx.jpg"};
        return files;
    }
    
    
}

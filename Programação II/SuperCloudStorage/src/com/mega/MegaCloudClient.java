package com.mega;

import java.io.File;
import java.io.InputStream;

public class MegaCloudClient {
    
    public void uploadFile(InputStream stream)
    {
        System.out.println("fazendo upload para Mega ...");
    }
    
    public File downloadFile(String fileName)
    {
        System.out.println("fazendo download de " + fileName + " no Mega");
        return null;
    }
    
    public String[] files()
    {
        String[] files = {"teste mega.txt", "imagem mega.jpg"};
        return files;
    }
    
    
}

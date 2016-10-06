package com.onedrive;

import java.io.File;
import java.io.InputStream;

public class OneDriveAPI {
    
    public void upload(InputStream stream)
    {
        System.out.println("fazendo upload para One Drive ...");
    }
    
    public File download(String fileName)
    {
        System.out.println("fazendo download de " + fileName + " no OneDrive");
        return null;
    }
    
    public String[] files()
    {
        String[] files = {"teste one drive.txt", "imagem one drive.jpg"};
        return files;
    }
    
    
}

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package adapters;

import com.onedrive.OneDriveAPI;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.logging.Level;
import java.util.logging.Logger;
import supercloudstorage.CloudService;

/**
 *
 * @author 5928036
 */
public class OneDriveAdapter implements CloudService {
    private OneDriveAPI client = new OneDriveAPI();
    
    @Override
    public String[] listFiles() {
        return client.files();
    }

    @Override
    public File download() {
        return client.download("");
    }

    @Override
    public void upload(String fileName) {
        try {
            client.upload(new FileInputStream(fileName));
        } catch (FileNotFoundException ex) {
            ex.printStackTrace();
        }
    }
    
}

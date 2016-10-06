/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package adapters;

import com.mega.MegaCloudClient;
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
public class MegaAdapter implements CloudService {
    private MegaCloudClient client = new MegaCloudClient();
    
    @Override
    public String[] listFiles() {
        return client.files();
    }

    @Override
    public File download() {
        return client.downloadFile("");
    }

    @Override
    public void upload(String fileName) {
        try {
            client.uploadFile(new FileInputStream(fileName));
        } catch (FileNotFoundException ex) {
            ex.printStackTrace();
        }
    }
    
}

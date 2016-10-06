package supercloudstorage;

import java.io.File;

/**
 * @author Elieser
 */
public interface CloudService {
    
    String[] listFiles();
    File download();
    void upload(String fileName);
    
}

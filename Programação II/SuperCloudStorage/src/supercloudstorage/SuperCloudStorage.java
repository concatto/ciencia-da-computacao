package supercloudstorage;

import adapters.DropBoxAdapter;
import java.io.File;
import java.util.Arrays;

/**
 * @author Elieser
 */
public class SuperCloudStorage {

    private final CloudService service = CloudServiceFactory.createCompositeCloudService();
    
    public String[] listFiles()
    {
        return service.listFiles();
    }
    
    public void upload(File f)
    {
        service.upload(f.getName());
    }
    
    public File download(String fileName)
    {
        return service.download();
    }
    
    public static void main(String[] args) {
        SuperCloudStorage storage = new SuperCloudStorage();
        System.out.println(Arrays.asList(storage.listFiles()));
    }
    
}

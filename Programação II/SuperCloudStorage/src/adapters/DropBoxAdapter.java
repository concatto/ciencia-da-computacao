package adapters;

import com.dropbox.DbxClientV2;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import supercloudstorage.CloudService;

public class DropBoxAdapter implements CloudService {

    private DbxClientV2 dbxClientV2 = new DbxClientV2();

    @Override
    public String[] listFiles() {
        return dbxClientV2.files();
    }

    @Override
    public File download() {
        return dbxClientV2.downloadAndFinish("teste.txt");
    }

    @Override
    public void upload(String fileName) {
        try {
            dbxClientV2.uploadAndFinish(new FileInputStream(fileName));
        } catch (FileNotFoundException ex) {
            ex.printStackTrace();
        }
    }

}

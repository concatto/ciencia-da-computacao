/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package supercloudstorage;

import adapters.DropBoxAdapter;
import adapters.MegaAdapter;
import adapters.OneDriveAdapter;

/**
 *
 * @author 5928036
 */
public class CloudServiceFactory {
    public static CloudService createDropboxService() {
        return new DropBoxAdapter();
    }
    
    public static CloudService createOneDriveService() {
        return new OneDriveAdapter();
    }
    
    public static CloudService createMegaService() {
        return new MegaAdapter();
    }
    
    public static CloudService createCompositeCloudService() {
        return new CloudServiceComposite(
                createDropboxService(),
                createMegaService(),
                createOneDriveService()
        );
    }
}

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package supercloudstorage;

import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 *
 * @author 5928036
 */
public class CloudServiceComposite implements CloudService {
    private List<CloudService> services = new ArrayList<>();
    
    public CloudServiceComposite(CloudService... services) {
        this.services.addAll(Arrays.asList(services));
    }
    
    void addService(CloudService service) {
        services.add(service);
    }
    
    @Override
    public String[] listFiles() {
        return services.stream().map(s -> s.listFiles()).flatMap(strings -> Arrays.stream(strings)).toArray(String[]::new);
    }

    @Override
    public File download() {
        for (CloudService s : services) {
            try {
                return s.download();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        
        return null;
    }

    @Override
    public void upload(String fileName) {
        services.forEach(s -> s.upload(fileName));
    }
    
}

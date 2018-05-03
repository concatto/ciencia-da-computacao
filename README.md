# Ciência da Computação
Repositório para arquivos relacionados ao curso de graduação em Ciência da Computação, pela Universidade do Vale do Itajaí.

Este repositório está [protegido](LICENSE.md) sob a licença GNU General Public License v3.0. Caso deseje utilizar trechos de código de arquivos deste repositório em seus projetos privados, entre em contato com o proprietário.


## Configuração do Git

```
[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12
$directory = "PortableGit"
$filename = "PortableGit-2.16.2-64-bit.7z.exe"
$path = "."
If (!(Get-ChildItem -Directory $env:HOMEPATH).Name.Contains($directory)) {
  $url = "https://github.com/git-for-windows/git/releases/download/v2.16.2.windows.1/$filename"
  Invoke-WebRequest $url -OutFile "$path/$filename"
  Start-Process "./$filename" -Wait
}
$env:PATH = "$env:PATH;C:$env:HOMEPATH/$directory/bin"


# Minified
[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12;$directory = "PortableGit";$filename = "PortableGit-2.16.2-64-bit.7z.exe";$path = ".";If (!(Get-ChildItem -Directory $env:HOMEPATH).Name.Contains($directory)) {  $url = "https://github.com/git-for-windows/git/releases/download/v2.16.2.windows.1/$filename"; Invoke-WebRequest $url -OutFile "$path/$filename";  Start-Process "./$filename" -Wait;}$env:PATH = "$env:PATH;C:$env:HOMEPATH/$directory/bin";

```

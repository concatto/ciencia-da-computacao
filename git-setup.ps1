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

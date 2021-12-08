:: Spin up a new Docker container ::
@ECHO OFF
:: Image name
set imageName="dockerwf"
docker run -dit --volume //c/Users/westo/WFHome:/home %imageName% bash & ECHO Successfully created container using image %imageName%. Use 'attach' to connect to container object.
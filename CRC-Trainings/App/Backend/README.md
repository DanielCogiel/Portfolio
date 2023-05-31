# App's backend (ExpressJS)

##### Backend configuration requires environment variables listed below:
- **SERVER_PORT** - defines on which port the server will listen
- **DB_HOST** - URL of website on which connected database is hosted
- **DB_NAME** - name of the connected database
- **DB_PORT** - port to access connected database
- **DB_USER** - name of user of database
- **DB_PASSWORD** - password of user of database

##### Also, in order to make migrations to the database using *db-migrate*, the *database.json* file is needed. An example file should look like this:
    {
        <<env>>: {
          "driver": <<db_driver>>,
          "host": <<db_host>>,
          "port": <<db_port>>,
          "user": <<db_user>>,
          "password": <<db_password>>,
          "database": <<db_name>>
        }
    }

You can define those in _.env_ file put in directory's root in case of local work or in environment configuration in case of other working environments.

##### You can run following scripts:
- *npm run build* - runs build of application
- *npm run dev* - runs the application in development environment
- *npm run start* - runs **built** application in production
- *npm run test* - runs unit tests defined in application 


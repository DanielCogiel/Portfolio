import express, {Express, Request, Response} from 'express'
import mysql from 'mysql';
import CourseModel from './interfaces/CourseModel';
import mapLanguage from './utility/mappers';
import cors from 'cors';
import bcrypt from 'bcrypt'
import multer from 'multer';
import fs from 'fs'
import 'dotenv/config'
import { checkCorrectLanguage, checkCorrectLevel, checkEmptyFields, checkStringMinMax } from './utility/validators';

const connection = mysql.createConnection({
    host: process.env.DB_HOST,
    port: parseInt(process.env.DB_PORT || '3306'),
    user: process.env.DB_USER,
    password: process.env.DB_PASSWORD,
    database: process.env.DB_NAME
})

connection.connect(error => {
    if (error) {
        console.error('Error connecting to database: ', error?.stack)
        return; 
    }
    console.log('Connection with database established.')
})

const upload = multer({
    dest: 'uploads/'
})

const API_URL: string = '/api'
const COURSES_URL: string = '/courses'
const PORT = process.env.SERVER_PORT;

const app: Express = express();

app.use(express.json());
app.use(cors());
app.use('/uploads', express.static('uploads'))

//gets all courses
app.get(`${API_URL}${COURSES_URL}/all`, (req: Request, res: Response) => {
    let data: CourseModel[] = [];
    connection.query('SELECT Users.id FROM Users WHERE Users.username = ?', [req.query.username], (error, id_row) => {
        if (id_row.length > 0) {
        const user_id = id_row[0].id || null;
        connection.query('SELECT Courses.id AS course_id, Enrolled.user_id AS enroll_id, Courses.owner_id AS owner_id FROM Users JOIN Enrolled ON Users.id = Enrolled.user_id RIGHT JOIN Courses ON Enrolled.course_id = Courses.id WHERE Courses.owner_id = ? OR Enrolled.user_id = ?;',
        [user_id, user_id], (error, bindedCoursesData) => {
            connection.query('SELECT Courses.id, Courses.level, Users.username, Courses.title, Courses.language, Courses.dateStart, Courses.dateFinish, Courses.hoursStart, Courses.hoursFinish, Courses.hoursTimes, Courses.location, Courses.trainer, Courses.imagePath FROM Courses JOIN Users ON Courses.owner_id = Users.id', [], 
            (error1, result) => {
                if (!error1) {
                    result.map((course: any) => {
                        let formattedLevel = course.level.toLowerCase().slice(1);
                        formattedLevel = course.level.charAt(0) + formattedLevel;
                        data = [...data, {
                            id: course.id,
                            owner: course.username,
                            title: course.title,
                            language: mapLanguage(course.language, true).toUpperCase(),
                            date: {
                                start: new Date(course.dateStart).toISOString().slice(0,10),
                                finish: new Date(course.dateFinish).toISOString().slice(0,10)
                            },
                            hours: {
                                start: course.hoursStart.slice(0, 5),
                                finish: course.hoursFinish.slice(0, 5),
                                times: course.hoursTimes
                            },
                            level: formattedLevel,
                            location: course.location,
                            trainer: course.trainer,
                            isEnrolled: !!bindedCoursesData.find((elem: any) => elem.course_id === course.id && elem.enroll_id === user_id),
                            isOwner: !!bindedCoursesData.find((elem: any) => elem.course_id === course.id && elem.owner_id === user_id),
                            image: course.imagePath
                        }]
                    })
                    res.json(data);
                } else {
                    res.status(500).json({message: 'SQL error: ' + error1.stack});
                }
            })
        })
    } else {
        res.status(500).json({message: 'No user was found.'})
    }
    })
})

//get personal courses
app.get(`${API_URL}${COURSES_URL}/personal`, (req: Request, res: Response) => {
    let data: CourseModel[] = [];
    connection.query('SELECT Users.id FROM Users WHERE Users.username = ?', [req.query.username], (error, id_row) => {
        if (id_row.length > 0) {
        const user_id = id_row[0].id;
        connection.query('SELECT Courses.id AS course_id, Enrolled.user_id AS enroll_id, Courses.owner_id AS owner_id FROM Users JOIN Enrolled ON Users.id = Enrolled.user_id RIGHT JOIN Courses ON Enrolled.course_id = Courses.id WHERE Courses.owner_id = ? OR Enrolled.user_id = ?;',
        [user_id, user_id], (error, bindedCoursesData) => {
            connection.query('SELECT Courses.id, Courses.level, Users.username, Courses.title, Courses.language, Courses.dateStart, Courses.dateFinish, Courses.hoursStart, Courses.hoursFinish, Courses.hoursTimes, Courses.location, Courses.trainer, Courses.imagePath FROM Courses JOIN Users ON Courses.owner_id = Users.id', [], 
            (error1, result) => {
                if (!error1) {
                    result.map((course: any) => {
                        let formattedLevel = course.level.toLowerCase().slice(1);
                        formattedLevel = course.level.charAt(0) + formattedLevel;
                        const isEnrolled: boolean = !!bindedCoursesData.find((elem: any) => elem.course_id === course.id && elem.enroll_id === user_id)
                        const isOwner: boolean = !!bindedCoursesData.find((elem: any) => elem.course_id === course.id && elem.owner_id === user_id)
                        if (isEnrolled || isOwner) {
                            data = [...data, {
                                id: course.id,
                                owner: course.username,
                                title: course.title,
                                language: mapLanguage(course.language, true).toUpperCase(),
                                date: {
                                    start: new Date(course.dateStart).toISOString().slice(0,10),
                                    finish: new Date(course.dateFinish).toISOString().slice(0,10)
                                },
                                hours: {
                                    start: course.hoursStart.slice(0, 5),
                                    finish: course.hoursFinish.slice(0, 5),
                                    times: course.hoursTimes
                                },
                                level: formattedLevel,
                                location: course.location,
                                trainer: course.trainer,
                                isEnrolled: isEnrolled,
                                isOwner: isOwner,
                                image: course.imagePath
                            }]
                        }
                    })
                    res.json(data);
                } else {
                    res.status(500).json({message: 'No user was found.'});
                }
            })
        })
    } else {
        res.status(500).json({message: 'SQL error: ' + error?.stack})
    }

    })
})

//get personal courses count
app.get(`${API_URL}${COURSES_URL}/personal/count`, (req: Request, res: Response) => {
    let count = 0;
    connection.query('SELECT Users.id FROM Users WHERE Users.username = ?', [req.query.username], (error, id_row) => {
        if (error) {
            res.json({message: ('SQL Error: ' + error.stack)})
        } else {
            if (id_row.length > 0) {
            const user_id = id_row[0].id || null;
            connection.query('SELECT Courses.id AS course_id, Enrolled.user_id AS enroll_id, Courses.owner_id AS owner_id FROM Users JOIN Enrolled ON Users.id = Enrolled.user_id RIGHT JOIN Courses ON Enrolled.course_id = Courses.id WHERE Courses.owner_id = ? OR Enrolled.user_id = ?;',
            [user_id, user_id], (err, bindedCoursesData) => {
                if (err) {
                    res.json({message: ('SQL Error: ' + err.stack)})
                }
                else {
                    connection.query('SELECT Courses.id, Courses.level, Users.username, Courses.title, Courses.language, Courses.dateStart, Courses.dateFinish, Courses.hoursStart, Courses.hoursFinish, Courses.hoursTimes, Courses.location, Courses.trainer, Courses.imagePath FROM Courses JOIN Users ON Courses.owner_id = Users.id', [], 
                (error1, result) => {
                if (!error1) {
                    result.map((course: any) => {
                        const isEnrolled: boolean = !!bindedCoursesData.find((elem: any) => elem.course_id === course.id && elem.enroll_id === user_id)
                        const isOwner: boolean = !!bindedCoursesData.find((elem: any) => elem.course_id === course.id && elem.owner_id === user_id)
                        if (isEnrolled || isOwner) {
                            count++;
                        }
                    })
                    res.json({count: count});
                } else {
                    res.status(500).json({message: 'SQL error: ' + error1.stack});
                }
            })
                }   
            })
        } else {
            res.status(500).json({message: 'No user was found.'})
        }

        }
    })
})

//deletes given course
app.delete(`${API_URL}${COURSES_URL}/:id/delete`, (req: Request, res: Response) => {
    const username = req.body.username
    const course_id = req.params.id
    connection.query('SELECT * FROM Users JOIN Courses ON Users.id = Courses.owner_id WHERE username = ? AND Courses.id = ?',
    [username, course_id], (error, result) => {
        if (error) {
            res.status(500).send('SQL Error: ' + error.stack)
        } else {
            if (result.length > 0) {
                connection.query('DELETE FROM Courses WHERE Courses.id = ?', [result[0].id], (error, deleteResult) => {
                    if (error) {
                        res.status(500).send('Could not delete given course.')
                    } else {
                        res.send('Course successfully deleted.')
                        fs.unlink(result[0].imagePath, (error) => {})
                    }
                })
            } else {
                res.status(404).send('Such course does not exist or you are not owner of this course.')
            }
        }
    })
})

//user leaves the course
app.delete(`${API_URL}${COURSES_URL}/:id/leave`, (req: Request, res: Response) => {
    const course_id = parseInt(req.params.id);
    const username = req.body.username;

    connection.query('DELETE e FROM Enrolled e JOIN Users ON e.user_id = Users.id WHERE Users.username = ? AND e.course_id = ?', 
    [username, course_id], (error, result) => {
        if (error) {
            res.status(500).send('SQL Error: ' + error.stack)
        } else {
            if (result.affectedRows === 1) {
                res.send('Successfully left course.')
            } else {
                res.status(500).send('Could not leave from course.')
            }
        }
    })  
})

//enrolls user to course
app.post(`${API_URL}${COURSES_URL}/:id/enroll`, (req: Request, res: Response) => {
    const course_id = parseInt(req.params.id);
    const username = req.body.username;

    connection.query('SELECT * FROM Users WHERE username = ?', [username], (error, result) => {
        if (error) {
            res.status(500).send('SQL Error: ' + error.stack)
        } else {
            connection.query("SELECT * FROM Enrolled WHERE user_id = ? AND course_id = ?", [result[0].id, course_id], (error1, result1) => {
                if (error1) {
                    res.status(500).send('SQL Error: '+ error1.stack)
                } else {
                    if (result1.length > 0) {
                        res.status(409).send('You already enrolled to this course.')
                    } else {
                        connection.query('INSERT INTO Enrolled(user_id, course_id) VALUES(?, ?)', [result[0].id, course_id], (error2, result2) => {
                            if (error2) {
                                res.status(500).send('SQL Error: ' + error2.stack)
                            } else {
                                if (result2.affectedRows > 0) {
                                    res.send('Successfully enrolled to course.');
                                } else {
                                    res.status(500).send('Could not enroll to this course.');
                                }
                            }
                        })
                    }
                }
            })
        }
    })
}) 

//registers course
app.post(`${API_URL}${COURSES_URL}/register`, upload.single('image'), (req: Request, res: Response) => {
    const {username, title, language, date, hours, level, location, trainer} = req.body
    const dateStart = JSON.parse(date).start;
    const dateFinish = JSON.parse(date).finish;
    const hoursStart = JSON.parse(hours).start;
    const hoursFinish = JSON.parse(hours).finish;
    const hoursTimes = JSON.parse(hours).times;

    if (checkEmptyFields(req.body) && checkEmptyFields(JSON.parse(date)) && checkEmptyFields(JSON.parse(hours)) 
    && checkStringMinMax(title, 10, 100) && checkStringMinMax(trainer, 3, 100) && checkCorrectLevel(level) 
    && checkCorrectLanguage(language)) {
        connection.query('SELECT * FROM Users WHERE username = ?', [username], (error, result) => {
            if (error) {
                res.status(500).send('SQL Error: ' + error.stack);
            } else {
                if (result[0].role !== 'CREATOR') {
                    res.status(403).send('You do not have permission to add any courses.')
                } else {
                    if (result.length > 0) {
                        const owner_id = result[0].id;

                        connection.query('INSERT INTO Courses(owner_id, title, language, dateStart, dateFinish, hoursStart, hoursFinish, hoursTimes, level, location, trainer, imagePath) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)',
                        [owner_id, title, mapLanguage(language), dateStart, dateFinish,
                            hoursStart, hoursFinish, hoursTimes, level.toUpperCase(), location, trainer, req.file?.path], 
                            (error: mysql.MysqlError | null, result: mysql.OkPacket) => {
                                if (error) {
                                    res.status(500).send('SQL Error: ' + error.stack)
                                } else {
                                    if (result.affectedRows != 0) {
                                        res.send('Added course successfully.')
                                    } else {
                                        res.status(500).send('Could not add given course.')
                                    }
                                }
                            });
                    } else {
                        res.status(404).send('No such user in the database.');
                    }
                }

            }
        })
    } else {
        res.status(400).send('Incorrect value format.')
    }
})

//registers user
app.post(`${API_URL}/register`, (req: Request, res: Response) => {
    const {username, password, confirmedPassword, name, surname, email, isCreator} = req.body;

    if (checkEmptyFields(req.body) 
    && checkStringMinMax(username, 5, 50)
    && checkStringMinMax(password, 5, 60)
    && checkStringMinMax(confirmedPassword, 5, 60)
    && checkStringMinMax(name, 2, 50) 
    && checkStringMinMax(surname, 2, 50) 
    && checkStringMinMax(email, 5, 255)) {
        if (password !== confirmedPassword) {
            res.status(422).send('Passwords do not match.')
        } else {
            bcrypt.genSalt(10, (errorSalt: Error | undefined, salt: string) => {
                if (!errorSalt) {
                bcrypt.hash(password, salt, (errorHash: Error | undefined, hashedPassword: string) => {
                    connection.query('SELECT * FROM Users WHERE username = ?', [username], ((error, results) => {
                        if (!error && results.length > 0) {
                            res.status(409).send(`User ${username} already exists.`)
                        } else {
                            connection.query('INSERT INTO Users(username, password, name, surname, email, role) VALUES (?, ?, ?, ?, ?, ?)', 
                            [username, hashedPassword, name, surname, email, isCreator ? 'CREATOR' : 'REGULAR'], (error, result) => {
                                if (error) {
                                    res.status(500).send('Error inserting user into database.');
                                } else {
                                    res.send('User added succesfully.')
                                }
                            })
                        }
                    }));
                })} else {
                    res.status(500).send('Internal server error.')
                }
            })
        }
    } else {
        res.status(400).send('Incorrect value format.')
    }
})

//logs user in
app.post(`${API_URL}/login`, (req: Request, res: Response) => {
    const {username, password} = req.body;

    connection.query('SELECT * FROM Users WHERE username = ? COLLATE utf8_bin', [username], (error, result) => {
        if (error) {
            res.status(500).json({
                isAuthenticated: false,
                message: 'Error trying to log in.'
            })
        } else {
            if (result.length > 0) {
                bcrypt.compare(password, result[0].password, (error, isAuthenticated) => {
                    if (isAuthenticated) {
                        res.json({
                            isAuthenticated: true,
                            role: result[0].role,
                            message: 'Login successful.'
                        });
                    } else {
                        res.status(401).json({
                            isAuthenticated: false,
                            message: 'Incorrect password.'
                        })
                    }
                })
            } else {
                res.status(404).json({
                    isAuthenticated: false,
                    message: 'No such user in the database.'
                })
            }
        }
    })
})

app.listen(PORT, () => {
    console.log(`Running on port ${PORT}...`)
})
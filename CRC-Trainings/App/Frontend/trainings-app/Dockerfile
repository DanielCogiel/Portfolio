FROM node:16
WORKDIR /usr/src/app
COPY . .
RUN npm ci
ARG REACT_APP_API_URL
ENV REACT_APP_API_URL=$REACT_APP_API_URL
RUN npm run build
EXPOSE 3000
CMD [ "npx", "serve", "build" ]

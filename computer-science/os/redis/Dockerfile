FROM python:3
ADD . /code
WORKDIR /code
RUN pip install -r requirements.txt
CMD python app.py

# run command
# docker build -t compose-flask .
# docker-compose up
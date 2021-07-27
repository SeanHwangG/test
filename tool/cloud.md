# Cloud

* computing resources are provisioned in a shareable way so that users get what they need when they need
* Best be defined as infrastructure as a service or IaaS
* Keep their data secure, accessible, and available
* Operate in lots of different geographic regions → easily duplicate your data across multiple sites

* Cloud computing: platform independent → increase mobility and productivity
  * more storage capacity

* [+] Cheap: Pay as you go, free tier
* [+] Scalability: dynamically increasing instances (Pokemon go)
* [+] Data safety: Backing up data across the globe in different data center
* [+] Extensibility: Built in monitoring, machine learning, block chain solution

> Terms

* On-prem: servieces of the business runs from within the confines of the organization
  * data stays in its own private network
  * [+] security: prevents potential data breach
  * [+] customization: unique solutions catering to their needs
  * [+] vendor lock-in: cost of switching to a differnt vendor is high (i-tunes)

* Serverless: No servers involved when running the service to remove infrastructure administration
  * Faas is a way to implmenet serverless

![cloud services](images/20210307_183109.png)

* IaaS (Infrastructure as a service): Don't worry about building your own network or your own servers
  * [ex] AWS, GCP, Azure

* PaaS (Platform as a service): abstracts away the server instances you need
  * subset of cloud computing where a platform is provided for customers to run their services
  * execution engine is provided for whatever software someone wants to run
  * web developer writing a application w/o entire server complete with file system, dedicated resources
  * [ex] AWS Elastic Beanstalk, Google app engine, Heroku

* SaaS (Software as a service): licensing use of software to others, keeping software centrally hosted and managed
  * [-] has to share it's data with service provider, limit to customization (ex. fix service down, high latency)
  * [ex] Google workspace, dropbox, salesforce

* FaaS (Function as a Service)
  * Event driven service model, only triggered when an event occurs (HTTP, web request)
  * [+] Batch job, cron job
  * [+] Easy to scale: stateless processes (image compression, video analysis)
  * [-] Cold start problem: depends on service provider, environment configuration, memory footprint
  * [-] Complexity: overall project becomes complex
  * [ex] Amazon's AWS lambda, Google Cloud function

* Hybrid Cloud: Sensitive in public, secure in private
* Multi cloud
  * [-] Increase in complexity
* Private Cloud: used by a single large corporation and generally physically hosted on its own premises
* Public Cloud: large cluster of machines run by another company

{% tabs %}
{% tab title='amazon' %}

![Sample architecture](images/20210403_015028.png)
[Show instances](https://us-west-2.console.aws.amazon.com/ec2/v2/home?)
[Install CLI](https://docs.aws.amazon.com/cli/latest/userguide/cli-configure-envvars.html)

* Amazon Web Service

> Terms

* env
  * export AWS_ACCESS_KEY_ID=AKIA..
  * export AWS_SECRET_ACCESS_KEY=XEu7/..
  * export AWS_DEFAULT_REGION=us-we
* fargate: automatically manages your containers, providing the correct computational resources to your application

* configure: create aws configuration in ~/.aws/credentials
  * list
* help

```txt
<!-- ~/.aws/config -->
[default]
region=us-west-2
output=json
```

```txt
<!-- ~/.aws/credentials -->
[default]
aws_access_key_id=AKIAUBU4SQ7HQRFTLW6S
aws_secret_access_key=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
```

{% endtab %}
{% tab title='google' %}

![Google](images/20210214_175023.png)

> Terms

* artifact
* container
* storage
  * Multi regional: frequent access
  * regional: cheap in certain region
  * nearline: infrequent access
  * coldline: long term backup

* OAuth2: Allows a user to give permission for an app to act on their behalf
  * Register your app with Google (provide a client id, and client secret)
  * Redirect user to authorization URL (happens on google’s server), Google shows consent screen
  * Google provides an authorization code
  * your app exchanges the code for a token and include token with subsequent requests to Google)

* OIDC: Extension to OAuth2 providing features for convenience
  * You register a third-party application as a client to the provider
  * The client sends a request to the provider’s authorization URL
  * The provider asks the user to authenticate / consent to the client acting on their behalf
  * The provider sends the client a unique authorization code
  * The client sends the authorization code back to the provider’s token URL
  * The provider sends the client tokens to use with other URLs on behalf of the user

* Project: Name must be longer than 6 character
* region: [ex] us-east
* zone: deployment area for Google Cloud resources within a region
  * a single failure domain within a region -> deploy across multiple zones in a region
  * [ex] asia-northeast3-b

> How to

* [Enable Billing](https://cloud.google.com/appengine/docs/python/console/#billing)
* [Moitoring](https://console.cloud.google.com/monitoring?project=seannote&timeDomain=1h)

![Gcloud](images/20210214_175053.png)

* Storage : 5GB / RAM: 1.7GB / CPU: 0.5vCPU
  * Free, can be boosted when necessary
* Built in python, node, php, docker, kubernates

* [Resource manager](https://console.cloud.google.com/cloud-resource-manager)
* [Images](https://console.cloud.google.com/gcr/images/seansdevnote?project=seansdevnote)

> Error ERROR: (gcloud.run.deploy) Cloud Run error: Container failed to start.
  Failed to start and then listen on the port defined by the PORT environment variable.
  Logs for this revision might contain more information

* doesn't run exec gunicorn

* --version: show version
* alpha / beta: combine with below commands to use new feature

* artifacts
  * repositories create quickstart-docker-repo --repository-format=docker --location=us-central1
  * repositories list

* app
  * deploy `app.yaml`: deploy app engine specified by `app.yaml`
    * --project `project_id`: deploy app.yaml
  * instantces
    * ssh `INSTANCE`: ssh to `INSTANCE`

* auth
  * configure-docker: register gcloud as a Docker credential
  * list: Show current active account
  * login: login to auth
  * print-access-token
  * revoke: logout

* builds
  * submit .: deploy defined configuration written in cloud.yaml
  * describe: get information about a particular build
  * --tag gcr.io/seansdevnote/flask-fire: builds docker in server dir
  * --config cloudbuild.yaml: use config file
  * --build-arg request_domain=mydomain

* cheat-sheet: show useful

* cloud-shell ssh

* component
  * install `kubectl`: install
  * update: process may take several minutes

* components
  * install docker-credential-gcr
  * update: update all components

* config: [ex] ~/.config/gcloud/configurations/config_default, ~/.kube/config
  * configurations list: manage multiple configurations
  * list: show all configuration
    * --kubeconfig=config-demo config unset contexts.gke_seannote_us-central1-a_api: unset contexts
  * set: Set a Cloud SDK property
    * project: change current project
  * unset: Unset a Cloud SDK property
  * get-contexts
  * get-value [project|compute/zone]
  * set run/platform managed run/region us-central1
  * view: show config in KUBECONFIG=~/.kube/config:~/.kube/kubconfig2

* delete

* init: authorize SDK tools to access cloud using credentials, default config
  * --console-only

* info: show commands

* info
  * --show-logs

* organizations
  * list

* projects

  * create: create new project
  * describe `PROJECT_ID`: Show metadata for a `PROJECT_ID` ([ex] classroom-316404)
  * get-iam-policy my_project
    * PROJECT_ID: Show all emails and roles
  * list: list all projects
    * --filter: [ex] 'parent.id=[ORGANIZATION_ID] AND parent.type=organization'

* run
  * deploy
    * --image gcr.io/seansdevnote/flask-fire: set image
  * services list: show all services
  * services describe name: show result of service

* topic: gcloud supplementary help ([ex] gcloudignore)

* topic: help command
  * gcloudignore

```sh
# 1. Deploy django
INSTANCE="sample"
USER="tom"
DB="db"
docker pull gcr.io/cloudsql-docker/gce-proxy:1.21.0
gcloud sql users create $USER -i $INSTANCE
gcloud sql databases -i $DB $INSTANCE

kubectl create secret generic cloudsql-oauth-credentials --from-file=credentials.json=[PATH_TO_CREDENTIAL_FILE]
kubectl create secret generic cloudsql --from-literal=username=[DATABASE_USERNAME] --from-literal=password=[PASSWORD]

docker build -t gcr.io/$INSTANCE/polls .
gcloud auth configure-docker
docker push gcr.io/$INSTANCE/polls
kubectl create -f polls.yaml  # Create the GKE resource

virtualenv env
source env/bin/activate
pip install -r requirements.txt

python manage.py makemigrations
python manage.py migrate
```

{% endtab %}
{% endtabs %}

## Service

![cloud services](images/20210307_183109.png)
![Cloud services share](images/20210607_221213.png)

* IaaS (Infrastructure as a service): User shouldn't have to worry about building your own network or your own servers
  * [ex] AWS, GCP, Azure

* PaaS (Platform as a service): abstracts away the server instances you need
  * subset of cloud computing where a platform is provided for customers to run their services
  * execution engine is provided for whatever software someone wants to run
  * web developer writing a application w/o entire server complete with file system, dedicated resources
  * [ex] AWS Elastic Beanstalk, Google app engine, Heroku

* SaaS (Software as a service): way of licensing use of software to others while keeping that software centrally managed
  * [-] share it's data with service provider, limit to the customization flexibility (fix service down, high latency)
  * [ex] Google workspace, dropbox, salesforce

* FaaS (Function as a Service): Event driven service model, only triggered when an event occurs (HTTP, web request)
  * [+] Batch job, cron job
  * [+] Easy to scale: stateless processes (image compression, video analysis)
  * [-] Cold start problem: depends on service provider, environment configuration, memory footprint
  * [-] Complexity: overall project becomes complex
  * [ex] Amazon's AWS lambda, Google Cloud function

## Cloud Setup

{% tabs %}
{% tab title='google' %}

* gcloud components update

```py
# 1. Setup in mac
curl https://stk.cloud.google.com | bash
exec -l $SHELL  # Restart shell
gcloud init
gcloud config set compute/zone asia-northeast3  # Setup zone

# 2. Simple frontend
echo "Hello World" > index.html
python -m SimpleHTTPServer 8080
""" preview on port 8080 """
```

![Shell](images/20210610_140324.png)

{% endtab %}
{% endtabs %}

## Notification Service

{% tabs %}
{% tab title='amazon' %}

> SES

* cost-effective, flexible, and scalable email service that enables developers to send mail from within any application
* complaint and bounce rates

> SNS

* Amazon Simple Notification Service

{% endtab %}
{% endtabs %}

## IAM

{% tabs %}
{% tab title='amazon' %}

* [Get root](https://console.aws.amazon.com/iam/home#/security_credentials)

![Get Root](images/20210426_213944.png)

* [IAM](https://console.aws.amazon.com/iam/home)

{% endtab %}
{% tab title='google' %}

* OS Login: simplifies SSH access management by linking your Linux user account to your Google identity
* Service account: can try to recover the account within 30 days
  * can be used by services and applications running on Compute Engine instance to interact with other Google Cloud APIs
  * Apps use its credentials to authorize to set of APIs and perform actions within permissions granted and VM instance

* User-managed service accounts
  * [ex] PROJECT_NUMBER-compute@developer.gserviceaccount.com (default, can be controlled)
* Google-managed service accounts
  * [ex] PROJECT_NUM@cloudservices.gserviceaccount.com (all projects enabled with CE come with a Google APIs)
  * [ex] service-PROJECT_NUMBER@compute-system.iam.gserviceaccount.com (Compute Engine System service account)

> gcloud iam CLI

* service-accounts
  * list: see all service accounts
  * keys list --iam-account githubaction@seansdevnote.iam.gserviceaccount.com

{% endtab %}
{% endtabs %}

### Service account

* special kind of account used by an application or a VM instance
* make authorized API calles
* identified by its email address, w/o passwords, and cannot log in via browsers / cookies
* associated with private/public RSA key-pairs that are used for authentication to Google
* can let other users or service accounts impersonate a service account

## Serverless

{% tabs %}
{% tab title='amazon' %}

> Lambda

* output connections should be both UDP, TCP
* Configure all application VPCs to be peered

> Terms

* BLueprint: Fastest way of configuring lambda
* Handler: To make testable from core logic
* Layer:  additional code or content can be provided for Lambda

{% endtab %}
{% tab title='google' %}

![web application](images/20210322_230844.png)
![mobile](images/20210322_230832.png)

* Fully managed serverless platform for developing and hosting web applications in multiple languages
* Standard: Less flexible, Fast deployment, applicable to free tier
* Flexible: Longer deployment

```sh
export GOOGLE_APPLICATION_CREDENTIALS=~/PATH_TO/service_account.json
export DB_CONNECTION_NAME=classroom-316404:asia-northeast3:db

# 1. Run proxy using cloudsql
docker run -d \
  -v ${GOOGLE_APPLICATION_CREDENTIALS}:/config \
  -p 127.0.0.1:5432:5432 \
  gcr.io/cloudsql-docker/gce-proxy:1.21.0 /cloud_sql_proxy \
  -instances=${DB_CONNECTION_NAME}=tcp:0.0.0.0:5432 \
  -credential_file=/config

# 2. deploy
python manage.py migrate
gcloud app deploy

# 3. Check deployment
gcloud app logs tail -s default
gcloud app browse
```

* yaml
  * **runtime**: [ex] nodejs10, python39

> Error

* can not find/execute Gunicorn
  * Remove gunicorn in your requirements.txt file unless you are specifying the entrypoint

```yml
# app.yaml
runtime: nodejs10
```

{% endtab %}
{% endtabs %}

## SQL

{% tabs %}
{% tab title='google' %}

* Last updated 2021 (approx)
* Cheaper for longer commitment

| -         | Monthly Price ($) |
| --------- | ----------------- |
| vCPU      | 30 / vCPU         |
| Memory    | 5.1 / GB          |
| HA vCPUs  | 60 / vCPU         |
| HA Memory | 10 / GB           |

> Term

* instance connection name: [ex] classroom-316404:asia-northeast3:db
  ![instance connection name](images/20210610_151328.png)

> gcloud sql CLI

* instances
  * list: list all database instance
  * describe `instance_id`: ([ex] db)
    * --project `project_id`: find `instance_id` in `project_id`
* databases
  * **-i=`instance`**
  * create `db`: create database
  * delete `db`: delete database
  * list
* connect `instance_name`
  * --user postgres
* users
  * **-i=`instance`**
  * create `user`: Create `user`
    * --password=`password`
  * delete `user`
  * list: show all uses

```sh
docker run -d \
  -v $SERVICE_ACCOUNT:/config \
  -p 127.0.0.1:5432:5432 \
  gcr.io/cloudsql-docker/gce-proxy:1.21.0 /cloud_sql_proxy \
  -instances=$DB_NAME=tcp:0.0.0.0:5432 \
  -credential_file=/config
```

{% endtab %}
{% endtabs %}

## VM

{% tabs %}
{% tab title='amazon' %}

* public ip address can be lost if you stop and start the instance
* Virtual machine at 10cent / hour,  billed hourly

* ami: Amazon Machine Images provides the information required to launch an instance
  * can launch multiple instances from a single AMI when you need multiple instances with the same configuration
  * Includes
    1+ Amazon EBS snapshots, or, for instance-store-backed AMIs, a template for the root volume of the instance
    (ex: an OS, an application server, and applications)
    Launch permissions that control which AWS accounts can use the AMI to launch instances
    A block device mapping that specifies the volumes to attach to the instance when it's launched
* [ex] C5: continuously has a heavy CPU load

* aws
  * reboot-instances
  * stop-instances
  * start-instances
    * --instance-ids

{% endtab %}
{% tab title='google' %}

* Shared-core: use context-switching to share a physical core between vCPUs for the purpose of multitasking
* E2 (General purpose): [ex] Web serving, app serving, small-medium databases
* N2, N2D, N1 (General purpose): [ex] Cache, Media, streaming
* M1, M2 (Memory-optimized): [ex] in-memory analytics
* C2 (Compute-optimized):
  * [ex] gaming, single-threaded applications, HPC, Electronic Design Automation
* A2 (Accelerator-optimized): optimized for high performance computing workloads
  * [ex] ML, HPC, massive parallelized computation

> Term

* OS Login: Compute Engine IAM roles to grant or revoke SSH access to your Linux instances

> gcloud compute CLI

* --project: [ex] seanhwangg
* addresses
  * list: list all address
* instances
  * add-metadata `instance`: must be a project member who is a compute instance admin
    * --metadata: [ex] block-project-ssh-keys=FALSE, enable-oslogin=TRUE
  * add-iam-policy-binding: grant OS login
  * list: see all instances
  * create `instance`
    * --zone: [ex] asia-northeast3-a
    * --machine-type: [ex] e2-micro
    * --subnet: [ex] default
    * --network-tier: [ex] PREMIUM
    * --maintenance-policy: [ex] MIGRATE
    * --service-account: [ex] 1933620077-compute@developer.gserviceaccount.com
    * --scopes: [ex] <https://www.googleapis.com/auth/devstorage.read_only>,...
    * --tags: [ex] http-server,https-server
    * --image: [ex] ubuntu-1804-bionic-v20210623
    * --image-project: [ex] ubuntu-os-cloud
    * --boot-disk-size: [ex] 10GB
    * --boot-disk-type: [ex] pd-balanced
    * --boot-disk-device-name: [ex] classroom
    * --no-shielded-secure-boot
    * --shielded-vtpm
    * --shielded-integrity-monitoring
    * --reservation-affinity=any
  * describe
  * reset `instance`: reset instance before the metadata takes effect by using
* networks
  * create: [ex] debug-network
* os-login
  * describe-profile: show all available login users
  * ssh-keys
    * add
      * --key-file=KEY_FILE_PATH
      * --ttl=EXPIRE_TIME
* project-info: read and manipulate project-level data like quotas and metadata
  * add-metadata
    * --metadata: [ex] enable-oslogin=TRUE
  * describe: describe the Compute Engine project resource
* zone
  * list: See all zones and regions

```sh
gcloud compute os-login ssh-keys add --key-file=/Users/sean/.ssh/google_compute_engine.pub --ttl=0
```

> USERNAME@VM_EXTERNAL_IP: Permission denied (publickey).

* If OS Login is enabled on your project, VM doesn't accept SSH keys that are stored in metadata
  * gcloud compute project-info add-metadata --metadata enable-oslogin=FALSE

{% endtab %}
{% endtabs %}

## Application Streaming

* Form of on-demand software distribution
* Essential portions of an application's code need to be installed on the computer
* While end user performs actions in application, necessary code and files are delivered over network as they needed

{% tabs %}
{% tab title='amazon' %}

* App stream

![app stream](images/20210412_214059.png)

1. Deliver desktop applications to any computer
    * Users can access the desktop applications they need at any time
    * streams your applications from AWS to any computer, including Chromebooks, Macs, and PCs
1. Scale without infrastructure
    * AppStream 2.0 is fully managed on AWS and globally available with pay-as-you-go pricing
    * Scale app streaming to many users across globe without acquiring, provisioning, and operating hardware or infrastructure
1. Secure applications and data
    * Apps and data are not stored on users' computers
    * Apps are streamed as encrypted pixels and access data secured within your network
    * Runs on AWS, so benefit from a data center and network architecture built for the most security-sensitive organizations
1. Provide a fluid and responsive user experience
    * Apps are highly responsive because they run on virtual machines
    * NICE DCV protocol automatically adjust each streaming session to network conditions for a fluid user experience
    * users can run multiple apps, easily switch and interact through an application centric view or a standard desktop experience
    * copy and paste between apps and local machine, quickly upload or download files, and print to local or network printers
    * can also listen to audio output from applications, and control the bandwidth and fidelity for the experience
1. Centrally manage applications
    * Each user accesses the same version of your applications
    * centrally manage applications on AppStream 2.0 and can stop managing installations and updates on each user's computer
1. Integrate with your IT
    * AppStream 2.0 connects to your Active Directory, network, cloud storage, and file shares
    * Users access applications using their existing credentials and your existing security policies manage access
    * Extensive APIs integrate AppStream 2.0 with your IT solutions

> Error

* File is deleted for new session
  * \\amznfsx7umcv4bw

{% endtab %}
{% tab title='google' %}

* Google Play Instant Apps: in 2017, aka Google Instant Apps, allows to use an app or game without installing it

{% endtab %}
{% endtabs %}

## Cloud Monitor

{% tabs %}
{% tab title='amazon' %}

* CloudWatch: monitoring and observability service built for DevOps engineers, developers, SRE
* cloudtrail
  ![Cloud Trail](images/20210504_182714.png)

{% endtab %}
{% tab title='google' %}

* Google Analytics 4: UA tracking ID starts with G-

> Terms

* Property

{% endtab %}
{% endtabs %}

## Orchestration

{% tabs %}
{% tab title='amazon' %}

* elastic beanstalk

![EBS](images/20210403_014445.png)
![EBS workflow](images/20210403_024508.png)
![EBS environment](images/20210403_024613.png)

* AWS fully managed service
* Get a notification when done
* Rollback by deploying previous version
* [Django deploy](https://docs.aws.amazon.com/elasticbeanstalk/latest/dg/create-deploy-python-django.html)

> Terms

* Application
  * [Manage](https://ap-northeast-2.console.aws.amazon.com/elasticbeanstalk/home?region=ap-northeast-2#/applications)
* Environment

> Error

* Environment named *** is in an invalid state for this operation. Must be Ready
  * Rebuild environment

![Environment named](images/20210427_050449.png)

* Failed to deploy application: During an aborted deployment, some instances may have deployed the new application version
  * Zip file name must be different

* [install](https://github.com/aws/aws-elastic-beanstalk-cli-setup)
* brew install awsebcli (github is preferred)
* pip install awsebcli

* Configuration
  * RDS_HOSTNAME
  * RDS_PORT
  * RDS_DB_NAME
  * RDS_USERNMAE
  * RDS_PASSWORD

* abort: Cancels an environment update or deployment
* clone: Clones an environment
* console: Opens the environment in the AWS Elastic Beanstalk Management Console
* config: open config file
* create `env`: Creates a new environment (init + prompt a series of questions)
* deploy
* health: Show
* init: create .elasticbeanstalk/config.yml file
  * -p `platform`: set platform (ex: python-3.9)
  * -i: interactive
  * --source SOURCE: code-commit
* list: Lists all environments
* logs: download logs
* open: Opens the application URL in a browser
* ssh: enter into eb instance
  * --setup
* status: Gets environment information and status
  * --verbose: show running instances
* terminate `env`: terminate environment
* use `env`: select environtment to `env`

```cfg
<!-- .ebextensions/django.config -->
container_commands:
  01_migrate:
    command: "source /opt/python/run/venv/bin/activate && python iotd/manage.py migrate --noinput"
    leader_only: true
```

> .ebextensions/db-migrate.config

* leader_only: executed once when deployed to multiple instance

{% endtab %}
{% endtabs %}

## Cloud Storage

{% tabs %}
{% tab title='amazon' %}

* Elastic Block Store

{% endtab %}
{% tab title='google' %}

* Goolge Cloud storage

* defacl
  * Get, set, or change default ACL on buckets
* du
* ls
* cp
  * `a.py` `gs://seansdevnote/`: copy `a.py` to `gs://seansdevnote/`
* mb (Make buckets)
  * -b off: uniform bucket-level access setting
* status
  * gsutil version: 4.55
* -m rsync -r ./static gs://[YOUR_GCS_BUCKET]/static

{% endtab %}
{% endtabs %}

## Container service

{% tabs %}
{% tab title='amazon' %}

* Elastic Container Service simplifies building, releasing, and operating production-ready containerized applications
* on ECS from a local development environment

> Terms

* Cluster: the logical grouping of ECS resources
* Service: resource that allows to run, maintain a specified # of instances of a task definition simultaneously, in ECS cluster
* Task-Definition: a text file, in JSON format, that contains all the definitions and configurations of your containers

* [Install CLI](https://docs.aws.amazon.com/cli/latest/userguide/install-cliv2-mac.html)
* --version
* configure
  * --cluster test
  * --default-launch-type FARGATE
  * --config-name test
  * --region eu-west-1
* up
  * --cluster-config test
  * --vpc YOUR_VPC_ID
  * --subnets YOUR_SUBNET_ID_1, YOUR_SUBNET_ID_2

{% endtab %}
{% tab title='google' %}

* container
  * get-credentials api
    * --zone us-central1-a
    * --project seannote
  * clusters create api
    * list
    * --scopes
    * --num-nodes
    * --zone `us-west1-a`
  * images list: list all images
  * images list-tags gcr.io/seansdevnote/page: list all tags

{% endtab %}
{% endtabs %}

## Load Balance

{% tabs %}
{% tab title='amazon' %}

* Elastic Load Balancing
* Application load balancer supports lambda as a target

{% endtab %}
{% tab title='google' %}

* Cloud load balancing

{% endtab %}
{% endtabs %}

## VPC Network

{% tabs %}
{% tab title='google' %}

![To Static](images/20210514_152832.png)

{% endtab %}
{% endtabs %}

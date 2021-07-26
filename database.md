# Database

| Sql                       | NoSQL                                                          |
| ------------------------- | -------------------------------------------------------------- |
| ACID compliance           | scalability (variaty of data), processing speed (high traffic) |
| structured and unchanging | cloud computing, storage / Rapid development                   |

* DynamoDB: Schemaless db, storing basic user attributes in an object-based format
* Neptune: high-performance graph database optimized for processing graph queries
* Redshift: large streams of user activity data

> Terms

* Data parallelism: parallelization across multiple processors focusing on distributing data across different nodes
  * can be applied on regular data structures like arrays and matrices by working on each element in parallel
* ETL: Extraction, Translation, Loading
  ![ETL](images/20210304_233925.png)
* Execution model: Batch vs Streaming
* integration: combining data from different sources into a single, unified view
  * Reduce data complexity | Adds value to data | Increase collaboration, availability | Unify data system
* Lambda Architecture
  * data-processing architecture designed to handle massive quantities of data both batch, stream processing
* Latency
  * Low: Game, Traffic
  * High: Search engine indexing
* ORM (Object Relation Mapping): Remove dependency: Doesn't depends on speicific database (MySQL, MongoDB)
  * Reduce error, automatically detect changes
* Schema on read: creates the schema only when reading the data → NoSql
* Schema on write: defined as creating a schema for data before writing into the database → SQL
* smart: Connect with other devices and have knowledge of the environment
* in situ: Bringing the computation to the location of the data
* rollback: process that reverts writes operations to ensure the consistency of all replica set members
* CAP: Can only achieve two of following
  * Consistency: Every read receives the most recent write or an error
  * Availability: Every request receives response, without guarantee that it contains the most recent write
  * Partition: Continues to operate despite any number of messages dropped by network between nodes
  ![CAP Theory](images/20210304_233840.png)

* ACID
  * Atomicity: all changes that we need to do for these promotions must happen altogether
  * Concurrency: multiple people updating a database simultaneously
  * Isolation: context of concurrency, multiple people updating a database simultaneously
  * Durability: once a transaction has been committed, it will remain so

* BASE: Basic Availability, Soft state, Eventual Consistency

* Fault Tolerance: enables a system to continue operating properly in the event of the failure of some of its components
  * Commodity cluster \(redundant data storage\)

* IaaS: User must install and maintain an operating system, and other applications
  * virtual machines, servers, storage, load balancers, network
  * Amazon EC2 cloud
* PaaS: Provided with entire computing platform
  * Execution runtime, database, web server, development tools
  * Google App engine, Microsoft Azure
* SaaS: cloud service provides hardware, software environment \(operating system, application software\) * Dropbox
* BDMS: Continuous data ingestion
  * Support for common “Big Data” data types
  * A full query language
  * A flexible semi-structured data model

> Question

* 6V of Big data
  * Volumes: brings cost, scalability, and performance related to their storage access and processing
  * Variety: structure (formats, models), media, semantic(interpret), availability(realtime vs intermittent)
  * Velocity: Data is being generated at an alarming rate (batch processing vs real-time processing)
  * Veracity: Uncertainty and inconsistencies in the data (data provenance)
  * Valence: Connectedness of big data in form of graphs (Complex Data Exploration Algorithm)
  * Value: Finding correct meaning out of the data

* How to solve challenges in big data integration?
  * Probabilistic Schema Mapping vs Pay-as-you-go Model

* 5 key points in order to categorize big data systems?
  * Execution model, Latency, Scalability, Programming Language, Fault Tolerance

* Why do companies use big data?
  * Higher scales | Improved Safety | Customer Satisfaction | Better Profit Margins
  * Efficient operations | Improved Product Placement (Personalized marketing)

* Why is it rising?
  * Access of larger storage becomes easier for everyone

* Why is mobile advertising related to big data?
  * Mobile advertising benefits from data integration with location which requires big data

* What are Big data policies?
  * privacy and lifetime | interoperability and regulation | curation and quality

* What is denormalization of data?
  * improve the read performance, at expense of write performance, add redundant copies | grouping data

* Three types of source: Business data | Sensor data | User data
* Things to take account
  * Frequency of updates | Consolidation rule → linking, missing data, dirty data (negative age)

{% tabs %}
{% tab title='javascript' %}

* Algolia
  * Simple text search
  * index.clearObjects()

* TypeDI

```js
import Container from "typedi"
Container.get(TypeService);
```

{% endtab %}
{% tab title='python' %}

* django
  * django.setup(): Setup django outside of django module
  * get_version(): Show version

{% endtab %}
{% endtabs %}

## Data Science

> Terms

* Transaction: a single logical operation on the data → must provide ACID
* Lake: vast pool of raw data, the purpose for which is not yet defined
* Silo: Data produced from an organization that is spread out
  * Bad unsynchronized and invisible data
  ![Silo](images/20210304_233808.png)
* Data Analyst: Discover Problem & Potential solution → Visualize, dashboard
  * Focus on Past & Present
* Scientist: Modeling
* Data Engineer
  * Data Architecture, Database maintenance \(Schema\), quality and pipelines

* Data Science
  ![Data Science](images/20210304_233946.png)

* Dashboard: promotes trasnparency, accountability
  * automatic data pipelines: dashboard
  * purpose, scope, layout + flow, consistent naming structure

## Warehouse

* repository for structured, filtered data that has already been processed for a specific purpose

{% tabs %}
{% tab title='java' %}

![Java](images/20210722_152711.png)

{% endtab %}
{% tab title='google' %}

* [+] Automate data delivary, make insight (realtime) accessible, protect business data, simplify data operations

* gcloud
  * bq
    * --help: Show help
    * head: show first ten row
    * ls: List dataset
    * show: show project info
      * `dataset`: [ex] bigquery-public-data:samples.wikipedia
      * dataset

{% endtab %}
{% endtabs %}

## DB Dimension

> Term

* Facts
  * Semi-additive: that can be summed up for some of the dimensions in the fact table

* Slowly Changing: depends on business requirement
* Rapidly Changing: do not need to track changes
* Junk: fact table is a single table with the combination of attributes to avoid multiple foreign keys
* Fixed: static dimensions are not extracted from real data source but created in the data warehouse context

## B Tree

* Every node has at most M children
* Every internal node has at least ⌈M|2⌉children
* The root has at least 2 children if it is not a leaf
* An internal node with k children contains k - 1 keys
* All leaves appear on the same level of the tree
* Property
  * parameter n: a node holds n search key values (sorted) and n+1 pointers (to interior nodes or records)
  * left key ≤ pointed-to value < right key
  * choose n so large that a node fits in a block
  * interior node: between half and all of the n+1 pointers are used
  * leaf node: rightmost pointer to the next leaf

* B+ Tree: Internal nodes contain only search keys (no data)
  * leaves have at least ⌈L | 2⌉ keys up to L keys
  * Balanced (equal length paths) trees for minimizing disk I|O
  * logarithmic levels maintained w.r.t. size of the data file
  * no overflow blocks (but insert, delete more complex)
  * guaranteed upper limits on access, insert, delete times
  * data file not sorted, then leafs have to constitute a dense index
  * data file sorted, then leafs may constitute a sparse index
  * number of children for a node, ⌈b | 2⌉ m  b     (only root can have two children)
  * In order to access a particular byte, track #, sector #, offset needed
  * Each block usually contains 512 bytes
  * Data must be brought to main memory (RAM)

## DB Index

* Data structures used for quickly locating tuples that meet a specific type of condition ([ex] equality, range)
* Many types of indexes: Evaluate them on access, insertion, deletion item, Disk Space needed

> Term

* Primary index: the index on the attribute (a.k.a. search key) that determines the sequencing of the table on disk
* Secondary index: index on any other attribute
* Dense index: every value of the indexed attribute appears in theindex
* Sparse index: many values do not appear
* insertion: if no new block is created then do nothing else create an index entry with the new value
  * how to find space: find nearby free space and slide blocks backward, or use an overflow block
* deletion: if the deleted entry appears in the index replace it with the next search-key value
  * (leave deleted value assuming no part of the system assume it still exists without checking the block)
* Multi-level indices: treat the index as data and build an index on it
* Roll up: periodic task that aggregates data from indices specified by index pattern, then rolls it into new index

{% tabs %}
{% tab title='python' %}

* django.db.models.indexes (or django.db.models)
  * Index()
    * name: less than 30 chars ([ex] **auto-generate**)
  [ex]
  (Lower('title').desc(), 'pub_date', name='lower_title_date_idx')
  (F('height') * F('weight'), Round('weight'), name='calc_idx')

{% endtab %}
{% tab title='sql' %}

```sql
SELECT
  EXTRACT (HOUR FROM time) AS hour, ad_id, website_id -- Dimensions
  COUNTIF(event = "start")                            -- Metrics
  COUNTIF(event = "complete")
FROM
  batches.batch_1234
GROUP BY
  hour, ad_id, website_id
```

{% endtab %}
{% endtabs %}

## Key

* Auto increment: Surrogate keys never need to change, even if all other columns in your table are possible to change
  * easier for RDBMS to ensure uniqueness without locking, race conditions, when users inserting concurrently
  * Int is most compact data type you can use for primary key, so it results in a smaller index than using a long string
  * Efficiency of inserting into B-tree indexes
* Alternative: combination of columns that could be a primary key, but isn't
* Candidate: Minimal Super Keys
* Foriegn
  * FOREIGN KEY (PersonID) REFERENCES Persons(PersonID)
  * PersonID column in the Orders table is a FOREIGN KEY in the Orders table
* Primary: Chosen candidate keys
  * cannot have null values in any tuple, table can have only one primary
* Super: A set of attributes SK of R such that no two tuples in any valid
  * relation instance r(R) will have the same value for SK
* composite: candidate key that consists of two+ aattributes (table columns) that together uniquely identify entity
* compound: composite key for which each attribute that makes up the key is a simple (foreign) key in its own right
* Natural Key
  * if column has some meaning for the entity, (ex. phone number) no extra column is needed for the surrogate key
  * table of shoes referencing colors would need to do a join if you wanted to get the color name

{% tabs %}
{% tab title='gcp' %}

* Big Query
  * Clustering: Frequently accessed table
  * Surrogate key: prefer UUID(), use hash derived from business key

{% endtab %}
{% endtabs %}

### UUID

* no network connection between multiple databases
* avoids attackers guessing url's to pages they shouldn't have access to

{% tabs %}
{% tab title='javascript' %}

* celebrate

```js
import { Joi, celebrate } from "celebrate";
const SaleValidation = Joi.object()
  .keys({
    name: Joi.string().min(1).max(10).required(), amount: Joi.number().min(0).optional(),
    percent: Joi.number().min(0).max(1).optional(),
  })
  .or("amount", "percent")
  .nand("amount", "percent");

export default {
  saleAdd: celebrate({ body: BuyFormValidation, }),
  saleGet: celebrate({ params: { name: Joi.string().min(1).max(10).required() } }),
  saleUpdate: celebrate({ params: { uuid: Joi.string().guid({ version: "uuidv4" }).required() } }),
  saleDelete: celebrate({ params: { uuid: Joi.string().guid({ version: "uuidv4" }).required() } }),
};

// Types
const schema = Joi.object().keys({
  type: Joi.string().valid('ios', 'android'),
});
```

{% endtab %}
{% endtabs %}

## Design

> Terms

* Functional Dependency
  * A->B holds if two tuples having same value of attribute A also have same value for attribute B

| STUD_NO | STUD_NAME | STUD_PHONE | STUD_STATE | STUD_COUNT RY | STUD_AG E |
| ------- | --------- | ---------- | ---------- | ------------- | --------- |
| 1       | RAM       | 9716271721 | Haryana    | India         | 20        |
| 2       | RAM       | 9898291281 | Punjab     | India         | 19        |
| 3       | SUJIT     | 7898291981 | Rajsthan   | India         | 18        |
| 4       | SURESH    |            | Punjab     | India         | 21        |

* Functional Dependencies STUD_NO->STUD_NAME, STUD_NO->STUD_PHONE hold but STUD_NAME->STUD_STATE do not hold

* Normalize
  * process of minimizing redundancy from a relation or set of relations

* One to Many

![One to Many](images/20210321_212309.png)

* Many to Many: Requires intermediary table

![Many to Many](images/20210321_212400.png)

* {STUD_NO -> STUD_NAME, STUD_NO -> STUD_STATE, STUD_STATE -> STUD_COUNTRY, STUD_NO -> STUD_AGE}

```sql
STUDENT (STUD_NO, STUD_NAME, STUD_PHONE, STUD_STATE, STUD_AGE)
STATE (STATE, COUNTRY)
```

* Algebra

* Projection
  $$ π $$

* Selection
  $$ \sigma $$

* Union

$$ \cup $$

* Difference

$$ - $$

* Join

$$ \bowtie $$

* Attribute Renaming

$$ \delta $$

{% tabs %}
{% tab title='sql' %}

```sh
# Find theaters showing movies by Bertolucci
{t : theater |  s ∈ schedule  m ∈ movie
  [t(theater) = s(theater) ∧ s(title) = m(title) ∧ m(director) = Bertolucci}

# Find the titles of all movies by “Berto”
{t: title| ∃m ∈ movie [m(director) = “Berto” ∧ t(title) = m(title)]}

# Find the pairs of actors acting together in some movie
π actor 1, actor2 ( δactor → actor1 (movie) ⋈ δactor → actor2( movie ) )

# Find the actors playing in every movie by Berto
π actor ( movie ) - πactor [ ( πactor ( movie ) ⋈ πtitle ( σdir=BERTO( movie ) ) ) - πactor, title( movie ) ]

# Find the actors playing in every movie by Berto
π title,actor(movie) ÷ πtitle(σdir=berto(movie))

# Find the names of customers who took every loan.
π cname,lno(borrower) ÷ π lno(δ no → lno(loan))     # fail when loan is empty
π name(customer) - πname ( πname(customer) ⋈ πno(loan) - δcname→name, lno→no(πcname,lno(borrower)) )

# List the directors such that every actor is cast in one of his|her movies.
π director,actor(movie) ÷ πactor(movie).        # fail when there is no actor
π director(movie) − πdirector[πdirector(movie) ⋈ πactor(movie) − πdirector,actor(movie)]

# The directors of all movies playing elsewhere than Hillcrest
π director[σtheater ≠ ‘Hillcrest’(movie ⋈ schedule)]    || expensive join
π director[π title, director(movie) ⋈ πtitle(σtheater ≠ 'Hillcrest'(schedule))]

# List the drinkers that frequent only bars that serve some beer that they like.
# (Assume each drinker likes at least one beer and frequents at least one bar.)
[frequents | drinker bar]
[serves | bar beer]
[likes | drinker beer]

πdrinker(frequents) − πdrinker[frequents−πdrinker,bar(serves ⋈ likes)]

# List the drinkers that frequent no bar that serves a beer that they like
πdrinker(frequents) − πdrinker(frequents ⋈ serves ⋈ likes)
```

{% endtab %}
{% endtabs %}

### Normal Form

* First Normal Form: Relation is in first normal form if it does not contain any composite or multi-valued attribute
  * There are only Single Valued Attributes
  * Attribute Domain does not change
  * There is a Unique name for every Attribute/Column
  * The order in which data is stored, does not matter

| STUD_NO | STUD_NAME | STUD_PHONE             | STUD_STATE | STUD_COUNTRY |
| ------- | --------- | ---------------------- | ---------- | ------------ |
| 1       | RAM       | 9716271721, 9871717178 | HARYANA    | INDIA        |
| 2       | RAM       | 9898297281             | PUNJAB     | INDIA        |
| 3       | SURESH    |                        | PUNJAB     | INDIA        |

* Multi-valued attributes in the table

| STUD_NO | STUD_NAME | STUD_PHONE | STUD_STATE | STUD_COUNTRY |
| ------- | --------- | ---------- | ---------- | ------------ |
| 1       | RAM       | 9716271721 | HARYANA    |              |
| 1       | RAM       | 9871717178 | HARYANA    | INDIA        |
| 2       | RAM       | 9898297281 | PUNJAB     | INDIA        |
| 3       | SURESH    |            | PUNJAB     | INDIA        |

* Second Normal Form
  * a relation must be in first normal form and relation must not contain any partial dependency
  * dependent on any proper subset of any candidate key of the table
  * [-] If we update only one tuple and not the other, the database would be in an inconsistent state

* Third Normal Form
  * reduce the duplication of data, avoid data anomalies, ensure referential integrity, simplify data management
  * free of insertion, update, deletion anomalies, and ensures functional dependency preserving and lossless

| STUD_NO | STUD_NAME | STUD_STATE | STUD_COUNTRY | STUD_AGE |
| ------- | --------- | ---------- | ------------ | -------- |
| 1       | RAM       | HARYANA    | INDIA        | 20       |
| 2       | RAM       | PUNJAB     | INDIA        | 19       |
| 3       | SURESH    | PUNJAB     | INDIA        | 21       |

> Question

* Make following table into 2NF

| STUD_NO | COURSE_NO | COURSE_FEE |
| ------- | --------- | ---------- |
| 1       | C1        | 1000       |
| 2       | C2        | 1500       |
| 1       | C4        | 2000       |
| 4       | C3        | 1000       |
| 4       | C1        | 1000       |
| 2       | C5        | 2000       |

* COURSE_FEE cannot alone decide the value of COURSE_NO or STUD_NO;
* COURSE_FEE together with STUD_NO cannot decide the value of COURSE_NO;
* COURSE_FEE together with COURSE_NO cannot decide the value of STUD_NO;
* COURSE_FEE would be a non-prime attribute, as it does not belong to one only candidate key {STUD_NO, COURSE_NO}
  * But, COURSE_NO -> COURSE_FEE, which is a proper subset of the candidate key
* Non-prime attribute COURSE_FEE is dependent on a proper subset of the candidate key, which is a partial dependency
  * so this relation is not in 2NF

| Table 1 |           | Table 2   |
| ------- | --------- | --------- | ---------- |
| STUD_NO | COURSE_NO | COURSE_NO | COURSE_FEE |
| 1       | C1        | C1        | 1000       |
| 2       | C2        | C2        | 1500       |
| 1       | C4        | C3        | 1000       |
| 4       | C3        | C4        | 2000       |
| 4       | C1        | C5        | 2000       |
| 2       | C5        |

## Relation

{% tabs %}
{% tab title='hasone.js' %}

* A HasOne B association
  * 1-1 relationship exists between A and B
  * foreign key being defined target B
* A HasMany B association
  * 1-n relationship exists between A and B
  * foreign key being defined in the target model (B)
* A BelongsTo B association
  * 1-1 relationship exists between A and B
  * foreign keys being defined in the source model (A)
  * should be added when we need an owner
  * Book.belongsTo(models.User)
* A BelongsToMany B association: n-n relationship exists between A and B, using table C as junction table
  * Table C has the foreign keys (automatically create the two attributes userId and profileId)
  * Sequelize will automatically create this model C (if not exists) and define appropriate foreign keys on it
  * getBars()
  * countBars()
  * hasBar()
  * hasBars()
  * setBars()
  * addBar()
  * addBars()
  * removeBar()
  * removeBars()
  * createBar()

```js
// 1. has One Many
User.hasOne(models.UserProfile, { foreignKey: { name: "userID", allowNull: false } });
db.food.hasMany(db.meal, {as : 'Food', foreignKey : 'foodID'});

// 2. belongs to
Match.belongsTo(models.User, {foreignKey: { name: "userID" } });

import { DataTypes, Model, Sequelize } from "sequelize";

export default (sequelize: Sequelize) => {
  class Match extends Model {
    static associate(models): void {
      Match.belongsTo(models.User, {
        foreignKey: { name: "userID" }
      });
      Match.belongsTo(models.Room, {
        foreignKey: { name: "roomID", allowNull: false }
      });
    }
  }
  return Match.init({
      id: {
        type: DataTypes.UUID,
        defaultValue: DataTypes.UUIDV4,
        primaryKey: true,
      },
    },
    { sequelize, modelName: "Match", ...modelOptions["general"] },
  );
};

// 3. automatically creates
// This creates a junction table `foo_bar` with fields `fooId` and `barId`
Foo.belongsToMany(Bar, { through: 'foo_bar' });
// This creates a junction table `foo_bar` with fields `fooId` and `barTitle`
Foo.belongsToMany(Bar, { through: 'foo_bar', targetKey: 'title' });
// This creates a junction table `foo_bar` with fields `fooName` and `barId`
Foo.belongsToMany(Bar, { through: 'foo_bar', sourceKey: 'name' });
// This creates a junction table `foo_bar` with fields `fooName` and `barTitle`
Foo.belongsToMany(Bar, { through: 'foo_bar', sourceKey: 'name', targetKey: 'title' });

const User = sequelize.define('user', { username: DataTypes.STRING, points: DataTypes.INTEGER }, { timestamps: false } );
const Profile = sequelize.define('profile', { name: DataTypes.STRING }, { timestamps: false } );
User.belongsToMany(Profile, { through: 'User_Profiles', foreignKey: "UserID"});
Profile.belongsToMany(User, { through: 'User_Profiles', foreignKey: "ProfileID"});
```

{% endtab %}
{% endtabs %}

## Relational algebra

```txt
# Find directors of current movies
{t: title | $$ \exists $$ s $$ \in $$ schedule [s(title) = t(title)]}

# Find the titles and the directors of all currently playing movies
{t: title, director | ∃s ∈schedule ∃m ∈ movie [s(title) = m(title) ∧ t(title) = m(title) ∧ t(director) = m(director)]}

# Find actors playing in every movie by Berto
{ a : actor |  y  movie [a(actor) = y(actor) m movie [m(dir) = ”Berto” t movie(m(title) = t(title)  t(actor) = y(actor))]]}
```

## ORM

{% tabs %}
{% tab title='python' %}

* sqlalchemy
  * detached: Object, states which an object can have within a session
  * dialect: Object, allows DB operations on a particular DB backend
  * DBAPI: Python Database API Specification
  * metadata: generally refers to "data that describes data"
  * create_engine('DB', echo=True): echo for logging

* sqlalchemy.engine: not thread-safe
  * underlying DBAPI connection may not support shared access between threads
  * begin(): Transaction Instance
  * Engine: Connects a Pool and Dialect together
    * begin(): Return a context manager delivering a Connection
    * connect(): Return a new Connection object
  * Connection: not thread-safe
    * execute(): Executes SQL statement construct, returns ResultProxy
  * Transaction
    * not thread safe
    * close()
    * commit()
    * rollback()

* sqlalchemy.schema
  * column
    * Column(name, type, primary_key=F): Column in a database table
  * Table
    * Table()
    * drop(engine)
    * columns
  * MetaData
    * MetaData(): Thread-safe container object for read
    * create_all(): check existence of each individual table. CREATE if not

```py
# to_sql
engine = sqlalchemy.create_engine("postgresql://user:password@host:port/database")
```

{% endtab %}
{% endtabs %}

### Eager loading

{% tabs %}
{% tab title='javascript' %}

```js
User.belongsToMany(Profile, { through: 'User_Profiles' });
Profile.belongsToMany(User, { through: 'User_Profiles' });

// 1. Lazy Loading
const amidala = await User.create({ username: 'p4dm3', points: 1000 });
const queen = await Profile.create({ name: 'Queen' });
await amidala.addProfile(queen, { through: { selfGranted: false } });
const result = await User.findOne({ where: { username: 'p4dm3' }, include: Profile });
console.log(result);


const awesomeCaptain = await Captain.findOne({
  where: {
    name: "Jack Sparrow"
  }
});
/* Do stuff with the fetched captain */
console.log('Name:', awesomeCaptain.name);
console.log('Skill Level:', awesomeCaptain.skillLevel);
/* Now we want information about his ship! */
const hisShip = await awesomeCaptain.getShip();
console.log('Ship Name:', hisShip.name);
console.log('Amount of Sails:', hisShip.amountOfSails);


// 2. Eager
const amidala = await User.create({
  username: 'p4dm3', points: 1000,
  profiles: [{ name: 'Queen', User_Profile: { selfGranted: true } }]
}, { include: Profile });

const result = await User.findOne({ where: { username: 'p4dm3' }, include: Profile });

const awesomeCaptain = await Captain.findOne({
  where: {
    name: "Jack Sparrow"
  },
  include: Ship
});
//// Now the ship comes with it
console.log('Name:', awesomeCaptain.name);
console.log('Skill Level:', awesomeCaptain.skillLevel);
console.log('Ship Name:', awesomeCaptain.ship.name);
console.log('Amount of Sails:', awesomeCaptain.ship.amountOfSails);
```

{% endtab %}
{% tab title='python' %}

```py
# 1. Call user and parent
user = User.objects.all()
parent = user.prefetch_related('parent')
```

> Reference

<http://ses4j.github.io/2015/11/23/optimizing-slow-django-rest-framework-performance/>

{% endtab %}
{% endtabs %}

### N + 1 selects

{% tabs %}
{% tab title='python' %}

```py
# 1. Select video with comments
comments = Comment.objects.filter(video__title__starts_with='The').select_related('video').all()
```

{% endtab %}
{% tab title='sql' %}

```sql
-- 1. Get all wheels in each cars
SELECT * FROM Cars;
-- BAD: For each Cars, N additional selects
SELECT * FROM Wheel WHERE CarId = ?
-- GOOD
SELECT * FROM Wheel
```

{% endtab %}
{% endtabs %}

## Sharding

* architecture that partitions data by key ranges, distributes data among two or more database instances
* [+] enables horizontal scaling
* [-] adds additional programming and operational complexity to your application
  * If your application is bound by read performance, you can add caches or database replicas.

> Term

* Algorithmic sharding: client can determine a given partition’s database without any help ([ex] consistent hashing)
  * doesn’t consider the payload size or space utilization
* Dynamic sharding: external locator service determines the location of entries. It can be implemented in multiple ways
  * [+] resilient to nonuniform distribution of data
* Entity groups: Store related entities in the same partition to provide additional capabilities within a single partition
  1. Queries within a single physical shard are efficient.
  1. Stronger consistency semantics can be achieved within a shard.
* Hierarchical keys & Column-Oriented DB: extend key-value stores, expressiveness of entity groups with hierarchical PK

## Django

> Terms

* app
  * Web application that does something
  * a Weblog system, a database of public records or a small poll app

* project
  * a collection of configuration and apps for a particular website

* cookie-cutter
  * --replay: use information entered previously (~/.cookiecutter_replay/cookiecutter-django.json)
  * [Deploy django on EC2 using docker](https://benjlindsay.com/posts/deploying-a-cookiecutter-django-site-on-aws)

```sh
pip install cookiecutter
cookiecutter https://github.com/pydanny/cookiecutter-django
```

> Reference

* Two Scoops of Django

> Error

* AppRegistryNotReady: Apps aren't loaded yet
  * adding an app in INSTALLED_APPS in the settings.py file but you do not have that app installed in your computer

* TypeError: can't compare offset-naive and offset-aware datetimes
  * datetime.datetime.now() -> timezone.now() (from django.utils import timezone)

* django.template.exceptions.TemplateDoesNotExist: home.html
  * Update INSTALLED_APPS from settings.py

* Unable to configure handler 'console'
  * formatters -> formatter in LOGGING config

* Manager isn't available; User has been swapped for 'pet.Person'
  * from django.contrib.auth.models import User -> from user.models import User

* makemigrations does nothing
  * migrate each app at a time

* django.db.migrations.exceptions.InconsistentMigrationHistory: Migration hitcount.0001_initial is applied
before its dependency base.0001_initial on database 'default'.
  * rm */migrations/* && rm db.sqlite3 and migrate again

* HINT: The 'USERNAME_FIELD' is currently set to 'email', you should remove 'email' from the 'REQUIRED_FIELDS
  * REQUIRED_FIELDS cannot contain the USERNAME_FIELD

* django.core.exceptions.ImproperlyConfigured: Cannot import `app`. Check that `project.module.ModuleConfig.name` is correct
  * name = `module` -> name = `project.module` (in apps.py)

## Docker

```yml
# local.yml
version: '3'

volumes:
  local_postgres_data: {}
  local_postgres_data_backups: {}

services:
  django:
    build:
      context: .
      dockerfile: ./compose/local/django/Dockerfile
    image: classroom_local_django
    container_name: django
    depends_on:
      - postgres
    volumes:
      - .:/app:z
    env_file:
      - ./.envs/.local/.django
      - ./.envs/.local/.postgres
    ports:
      - "8000:8000"
    command: /start

  postgres:
    build:
      context: .
      dockerfile: ./compose/production/postgres/Dockerfile
    image: classroom_production_postgres
    container_name: postgres
    volumes:
      - local_postgres_data:/var/lib/postgresql/data:Z
      - local_postgres_data_backups:/backups:z
    env_file:
      - ./.envs/.local/.postgres

  docs:
    image: classroom_local_docs
    container_name: docs
    build:
      context: .
      dockerfile: ./compose/local/docs/Dockerfile
    env_file:
      - ./.envs/.local/.django
    volumes:
      - ./docs:/docs:z
      - ./config:/app/config:z
      - ./classroom:/app/classroom:z
    ports:
      - "7000:7000"
    command: /start-docs

# deploy.yml
version: '3'

volumes:
  production_postgres_data: {}
  production_postgres_data_backups: {}
  production_traefik: {}

services:
  django:
    build:
      context: .
      dockerfile: ./compose/production/django/Dockerfile
    image: classroom_production_django
    depends_on:
      - postgres
      - redis
    env_file:
      - ./.envs/.production/.django
      - ./.envs/.production/.postgres
    command: /start

  postgres:
    build:
      context: .
      dockerfile: ./compose/production/postgres/Dockerfile
    image: classroom_production_postgres
    volumes:
      - production_postgres_data:/var/lib/postgresql/data:Z
      - production_postgres_data_backups:/backups:z
    env_file:
      - ./.envs/.production/.postgres

  traefik:
    build:
      context: .
      dockerfile: ./compose/production/traefik/Dockerfile
    image: classroom_production_traefik
    depends_on:
      - django
    volumes:
      - production_traefik:/etc/traefik/acme:z
    ports:
      - "0.0.0.0:80:80"
      - "0.0.0.0:443:443"

  redis:
    image: redis:5.0

  awscli:
    build:
      context: .
      dockerfile: ./compose/production/aws/Dockerfile
    env_file:
      - ./.envs/.production/.django
    volumes:
      - production_postgres_data_backups:/backups:z
```

* include()
  * include other URL patterns
  * admin.site.urls is the only exception to this

* path()
  * route: string that contains a URL pattern
  * view, and two optional: kwargs, and name

## Apps

* Django contains a registry of installed applications that stores configuration and provides introspection
  * registry is called apps and it’s available in django.apps
* maintains a list of available models.

* apps
  * get_app_config(`model`)
  * get_model(`app_label`, `model_name`, `require_ready`=True): Returns Model with `app_label` and `model_name`
    * Raises LookupError if no such application or model exists

```py
from django.apps import apps

print(apps.get_app_config('admin').verbose_name)

# 1. Avoid circular import
model = apps.get_model('app_name', 'ModelName')
```

### Messages

* Display message on top of django websites

* success()

```html
{% if messages %}
  {% for message in messages %}
    <div class="alert-{{message.tags}}">
      {{message}}
    </div>
  {% endfor %}
{% endif %}
```

## Db

* reset_queries(): reset saved queries
* connection
  * queries: list of queries

* transaction
  * non_atomic_requests(using=None)

* db.field
  * unique=**True**
  * Null=**False**
  * Blank=**False**
  * Default=**None**
  * help_text=**None**
  * primary_key=**False**
  * AutoField(): Autoincremented integer field
  * CharField(max_length=255, choices): single line view
  * DurationField()
  * EmailField()
  * ForeignKey(`cls`): id of record in another table
    * `to`: can be a string to escape circular dependency
    * on_delete: specify action when key is deleted
      * CASCADE: object referenced by a ForeignKey is deleted, the object containing also deleted
      * PROTECT: throw error if ForeignKey is deleted
      * SET_DEFAULT: change to default only if default exists
  * GenericIPAddressField()
  * ImageField(): stores the path from `MEDIA_ROOT`
  * ManyToManyField(`Table`)
  * NullBooleanField():
  * SlugField(max_length=50): short label for something, containing only letters, numbers, underscores or hyphens
    * allow_unicode: default False
  * SmallAutoField: an AutoField, but only allows values under a certain (database-dependent) limit. Values from 1 to 32767
  * TextField(): Multi line view
  * TimeField()
    * auto_now=False
    * auto_now_add=False
  * URLField(max_length=200): vaidated by URLValidator
  * UUIDField(): good alternative to AutoField for primary_key
    * stores in a uuid datatype used on PostgreSQL, otherwise in a char(32)

  * transaction: decorator
    * .non_atomic_requests
    * create(), bulk_create(), get_or_create(), update() generally use transactions

> Q

* ~Q(): not
* Q(first_name__startswith='R')|Q(last_name__startswith='D'): or using Q

```py
from pprint import pprint
from django.db import connections
from django.db import DatabaseError, transaction

# 1. Q objects
from django.db.models import Q
from promos.models import Promo

Q(question__startswith='What')
Q(pub_date=date(2005, 5, 2)) | Q(pub_date=date(2005, 5, 6))

def fun_function(name=None):
  results = Promo.objects.active()
  results = results.filter(Q(name__startswith=name) |
                           Q(description__icontains=name)
  results = results.exclude(status='melted')
  results = results.select_related('flavors')
  return results

# 2. Print previous query
pprint([e['sql'] for e in connections['default'].queries])
print(connection.settings_dict['NAME'])

# 3. Transaction
try:
  with transaction.atomic():
    parent = Parent(name = "my name")
    parent.save()

    child = Child(number=3, parent=parent)
    child.save()
except DatabaseError:
  # Handle the case where an error prevented the operation

@transaction.atomic
def viewfunc(request):
    # This code executes inside a transaction.
    do_stuff()
```

### Db.models

* TextChoices

* Model: superclass of every models
  * Meta: subclass of Model
    * abstract=`True`: make class as abtract
    * db_table = `prefix`: set prefix for table name (ex: `prefix`_tablename)
    * unique_together: composite key (deprecated in favor of UniqueConstraints)
* models.base.ModelBase
  * all(): get all database
    * Avg / Min / Max / Sum()
  * create() -> object: creating an objectsand savie in one step
  * exclude()
  * filter(): filter by database
    * `field`__range=(`min`, `max`): filter by range
    * `model_name`__`column`: filter by forien key
    * `first_name`__startwith: start with
    * `user_id`__in=`Subquery()`: subqury
  * full_clean(): Model.clean_fields(), Model.clean(), Model.validate_unique()
  * clean_fields(): Raise ValidationError
    * exclude=`field`: set `field` to exclude ([ex] **None**)
  * validate_unique(): Raise ValidationError if not unique
  * get(): get one from database
  * get_or_create() -> Tuple(object, created): created object, boolean specifying whether a new object was created
    * defaults: dictionary to update field (other is to find)
  * order_by(`*args`): sort by `args`
    * \- to reverse the order
    * "?": for random
    * first(): get first after order_by
  * update_or_create() -> Tuple(object, created): created object, boolean specifying whether a new object was created

* functions
  * Lower(): (ex: order_by(Lower('name')), annotate(l_name=Lower('name')).order_by('l_name').values_list('name', flat=True))
    * `fieldname`

* F(): represents the value of a model field or annotated column

> Model methods

* model methods should act on a particular model instance vs Manager methods are intended to do “table-wide” things

* save(): override to customize saving behavior
  * auto-incremented value will be calculated and saved as an attribute on your object the first time
  1. Emit a pre-save signal. The pre_save signal is sent, allowing any functions listening for that signal to do something
  1. Preprocess the data. Each field’s pre_save() method is called to perform any automated data modification that’s needed
      * [ex] the date/time fields override pre_save() to implement auto_now_add and auto_now
  1. Prepare the data for the database
      * Each field’s get_db_prep_save() is asked to provide its current value in a data type that can be written to database
  1. Insert the data into the database : prepared data is composed into an SQL statement for insertion into the database
  1. Emit a post-save signal. The post_save signal is sent, allowing any functions listening for that signal to do something

* \_\_str__(): string representation of any object in admin page
* get_absolute_url(): Django how to calculate the URL for an object

* Model.from_db(): used to customize model instance creation when loading from the database
  * `db`: argument contains the database alias for the database the model is loaded from
  * field_names, values

```py
from .models import Book, User

# 1. CRUD
Book.objects.filter(title="A") | Book.objects.filter(title="B") # or
Book.objects.filter(title="A", title="B")                       # and
Book.objects.exclude(title="A")                                 # Not
User.objects.filter(membership__team_id="prake")                # Join

user.email="helsinki@gmail.com"
user.save()

""" get_or_create() """
try:
  obj = User.objects.get(first_name='John', last_name='Lennon')
except User.DoesNotExist:
  obj = User(first_name='John', last_name='Lennon', birthday=date(1940, 10, 9))
  obj.save()

""" update_or_create() """
defaults = {'first_name': 'Bob'}
try:
  obj = User.objects.get(first_name='John', last_name='Lennon')
  for key, value in defaults.items():
    setattr(obj, key, value)
  obj.save()
except User.DoesNotExist:
  new_values = {'first_name': 'John', 'last_name': 'Lennon'}
  new_values.update(defaults)
  obj = User(**new_values)
  obj.save()

""" Bulk update"""
objs = [
  Entry.objects.create(headline='Entry 1'),
  Entry.objects.create(headline='Entry 2'),
]
objs[0].headline = 'This is entry 1'
objs[1].headline = 'This is entry 2'
Entry.objects.bulk_update(objs, ['headline'])

# 2. Order choice models
from django.db import models
class IceCreamOrder(models.Model):
  FLAVOR_CHOCOLATE = 'ch'
  FLAVOR_VANILLA = 'vn'
  FLAVOR_STRAWBERRY = 'st'
  FLAVOR_CHUNKY_MUNKY = 'cm'
  FLAVOR_CHOICES = (
  (FLAVOR_CHOCOLATE, 'Chocolate'),
  (FLAVOR_VANILLA, 'Vanilla'),
  (FLAVOR_STRAWBERRY, 'Strawberry'),
  (FLAVOR_CHUNKY_MUNKY, 'Chunky Munky')
  flavor = models.CharField(max_length=2, choices=FLAVOR_CHOICES)

# 3. From Json
os.environ["DJANGO_SETTINGS_MODULE"] = "classroom.settings"
django.setup()

baekjoon = Site.objects.get(name="baekjoon")
with open("data/user.ignore", "r") as f:
  user_dics = json.load(f)
  team = Team.objects.create(name="prake")
  Site.objects.create(name="baekjoon")
  for user_dic in user_dics:
    user = User.objects.create(email=user_dic["email"], name=user_dic["name"])
    Membership.objects.create(user=user, team=team)
    Account.objects.create(user=user, site=baekjoon, name=user_dic["bj"])

# 4. Image Model
class Model(model.Model):
  _image=models.ImageField(upload_to='folder')
  thumb=models.ImageField(upload_to='folder')
  description=models.CharField()

  def set_image(self, val):
    self._image = val
    self._image_changed = True # Enusure image is not resized when description changes

    # Or put whole logic in here
    small = rescale_image(self.image,width=100,height=100)
    self.image_small=SimpleUploadedFile(name,small_pic)

  def get_image(self):
    return self._image

  image = property(get_image, set_image)

  # this is not needed if small_image is created at set_image
  def save(self, *args, **kwargs):
    if getattr(self, '_image_changed', True):
      small=rescale_image(self.image,width=100,height=100)
      self.image_small=SimpleUploadedFile(name,small_pic)
    super(Model, self).save(*args, **kwargs)

# 5. Singleton Object
class Origin(models.Model):
  name = models.CharField(max_length=100)
  def save(self, *args, **kwargs):
    if self.__class__.objects.count():
      self.pk = self.__class__.objects.first().pk
    super().save(*args, **kwargs)

from django.db.models import DEFERRED

# 6. Default implementation of from_db() (subject to change and could be replaced with super()).
@classmethod
def from_db(cls, db, field_names, values):
  if len(values) != len(cls._meta.concrete_fields):
    values = list(values)
    values.reverse()
    values = [values.pop() if f.attname in field_names else DEFERRED for f in cls._meta.concrete_fields]
  instance = cls(*values)
  instance._state.adding = False
  instance._state.db = db
  # customization to store the original field values on the instance
  instance._loaded_values = dict(zip(field_names, values))
  return instance
```

### Db.models.function

* Use functions provided by the underlying database as annotations, aggregations, or filters
* Functions are also expressions, so they can be used and combined with other expressions like aggregate functions

```py
from django.db.models import Value
from django.db.models.functions import Concat

# 1. Function
class Person(models.Model):
  first_name = models.CharField(max_length=50)
  last_name = models.CharField(max_length=50)

  @property
  @admin.display(ordering=Concat('first_name', Value(' '), 'last_name'))
  def full_name(self):
    return self.first_name + ' ' + self.last_name
```

* db.models.manager: Interface through which database query operations are provided to Django models
  * If no managers are declared on a model / parents, automatically creates the objects manager
  * Can have multiple managers on the same mode
  * get_queryset(): return a QuerySet with the properties you require

```py
from django.db import models
from django.db.models.functions import Coalesce

# 1. Query annotation
class PollManager(models.Manager):
  def with_counts(self):
    return self.annotate(num_responses=Coalesce(models.Count("response"), 0))

class OpinionPoll(models.Model):
  question = models.CharField(max_length=200)
  objects = PollManager()

class Response(models.Model):
  poll = models.ForeignKey(OpinionPoll, on_delete=models.CASCADE)
```

### Db.models.query

* avoid writing common queries all over our codebase and instead referring them using an easier to remember abstraction

* QuerySet : (ex: user.objects.all() returns queryset)
  * query: SQL equivalent
  * annotate(): write to db
  * bulk_create(`objs`): inserts the provided list of objects into the database in an efficient manner
    * ignore_conflicts=True: database ignore failure to insert any rows that fail constraints ([ex] duplicate unique values)
  * bulk_update(`objs`, `fields`): save the changes, so more efficient than iterating through list of models and save()
    * model’s save() method will not be called
  * count(): count number of element
  * delete(): truncate all element
  * exists(): Returns if the QuerySet contains any results
  * union(): get union of two querysets
  * values('title'): fetch only particular field
  * values_list('title'): fetch only particular field as list
    * flat=True: return without tuple

* FieldLookup : i- is case insensitive
  * exact / iexact
  * contains / icontains
  * in
  * gt / gte / lt / lte: compare values
  * startswith
  * istartswith
  * endswith
  * iendswith
  * range
  * date
  * year
  * iso_year
  * month
  * day
  * week
  * week_day
  * iso_week_day
  * quarter
  * time
  * hour
  * minute
  * second
  * isnull
  * regex
  * iregex

```py
# 1. User.manager.doctors.with_specialization('Dermatology')
from django.db.models.query import QuerySet
class ProfileQuerySet(QuerySet):
  def doctors(self):
    return self.filter(user_type="Doctor", user__is_active=True)

  def with_specializations(self, specialization):
    return self.filter(specializations=specialization)

  def users(self):
    return self.filter(user_type="Customer", user__is_active=True)

ProfileManager = ProfileQuerySet.as_manager
class Profile(models.Model):
  manager = ProfileManager()

# 2. Delete that doesn't have a foriegn key
for problem in Problem.objects.filter():
  if not hasattr(problem, "embed"):
    problem.delete()
```

## Dispatch

* receiver

```py
from django.db.models.signals import pre_save
from django.dispatch import receiver

@receiver(pre_save, sender=Hero, dispatch_uid="update_hero_count")
def update_hero_count(sender, **kwargs):
  hero = kwargs['instance']
  if hero.pk:
    Category.objects.filter(pk=hero.category_id).update(hero_count=F('hero_count')+1)

@receiver(pre_save, sender=Villain, dispatch_uid="update_villain_count")
def update_villain_count(sender, **kwargs):
  villain = kwargs['instance']
  if villain.pk:
    Category.objects.filter(pk=villain.category_id).update(villain_count=F('villain_count')+1)
```

## Templates

{% tabs %}
{% tab title='python' %}

* Request context to pass variable in tempates

* | truncatewords:`num`: trunctate words

* \_\_count: get length of queryset
  * more efficient than |length
* defaultfilters
  * stringfilter

```py
from django import template
from django.template.defaultfilters import stringfilter

import markdown as md

register = template.Library()


@register.filter()
@stringfilter
def markdown(value):
  return md.markdown(value, extensions=['markdown.extensions.fenced_code'])
```

{% endtab %}
{% endtabs %}

## View

![views](images/20210503_225430.png)

* Placed at PROJECT/urls.py
* Should contain as little logic as possible, mostly just a pointer to each of your apps specific URLConf’s
* A view function, or view for short, is simply a Python function that takes a Web request and returns a Web response
* Each view function is responsible for returning an HttpResponse object

* generic
  * View
  * CreateView
    * form_valid(self, form): custom logic for valid form
    * form_invalid(self, form): custom logic for invalid form
  * DeleteView
  * RedirectedView
  * UpdateView
  * ListView
  * TemplateView
  * base.ContextMixin
    * allow_empty: specifying whether to display the page if no objects are available
    * model: model that this view will display data for
    * queryset: A QuerySet that represents objects, If provided, the value of queryset supersedes value provided for model
    * paginate_by: An integer specifying how many objects should be displayed per page
    * get_queryset(): Get the list of items for this view
    * get_ordering(): a string (or iterable of strings) that defines the ordering that will be applied to the queryset

```py
from django.contrib.auth.mixins import LoginRequiredMixin
from django.views.generic import CreateView, UpdateView, TemplateView
from .models import Flavor

# 1. Simple Create Update view
class TitleSearchMixin:
  def get_queryset(self):
    # Fetch the queryset from the parent's get_queryset
    queryset = super(TitleSearchMixin, self).get_queryset()
    # Get the q GET parameter
    q = self.request.GET.get('q')
    if q:
      # return a filtered queryset
      return queryset.filter(title__icontains=q)
      # No q is specified so we return queryset
    return queryset

class FlavorCreateView(LoginRequiredMixin, CreateView):
  model = Flavor
  fields = ['title', 'slug', 'scoops_remaining']

class FlavorUpdateView(LoginRequiredMixin, UpdateView):
  model = Flavor
  fields = ['title', 'slug', 'scoops_remaining']

class FlavorListView(TitleSearchMixin, ListView):
  model = Flavor

# 2. Template view for html
class FreshFruitMixin:
  def get_context_data(self, **kwargs):
    context = super(FreshFruitMixin, self).get_context_data(**kwargs)
    context["has_fresh_fruit"] = True
    return context

class FruityFlavorView(FreshFruitMixin, TemplateView):
  template_name = "fruity_flavor.html"
```

> urls

* path("path", views.home)
  * name: [optional] "index"
* resolve('/')

## Utils

* timezone
  * now(): return current time

* html
  * format_html(): print html tag as is
  * list_per_page = `int`: set number of rows to display
  * list_display: column list
  * list_editable: editable dropdown
    * must be present in list_display
  * list_filter: filter on right
  * ordering: default ordering
  * search_fields: search field on top

```py
from django.utils.html import format_html

class LawyerAdmin(admin.ModelAdmin):
  list_display = ['show_firm_url', ...]

  def show_firm_url(self, obj):
    return format_html("<a href='{url}'>{url}</a>", url=obj.firm_url)

  show_firm_url.short_description = "Firm URL"
```

* text
  * slugify: make readable url for readability and SEO

```py
from django.utils.text import slugify
class Article(models.Model):
  headline = models.CharField(max_length=100)
  slug = models.SlugField(unique=True)

  def save(self, *args, **kwargs):
    self.slug = slugify(self.headline)
    super(Article, self).save(*args, **kwargs)


"""
u1 = User.objects.get(id=1)
from datetime import date
a1 = Article.objects.create(headline="todays market", pub_date=date(2018, 3, 6), reporter=u1)
a1.save() # automatically create
a1.slug # 'todays-market'
"""
```

### Functional

* cached_property: decorator for caching

```py
from django.utils.functional import cached_property

class Person(models.Model):
  @cached_property
  def friends(self):
```

## Admin page

{% tabs %}
{% tab title='python' %}

* admin
  * register(`Team`): decorator for registering Admin class
  ![List Display](images/20210503_230633.png)
  * ModelAdmin: Admin class for dealing with customizing the interface
    * [view_page]
    * actions: A list of actions to make available on the change list page
    * empty_value_display = `-`: overrides the default display value for record’s fields that are empty
    * search_fields
    * list_display
    * list_filter
    * [edit_page]
    * classes: list or tuple containing extra CSS classes to apply to the fieldset
    * exclude: if given, be a list of field names to exclude
    * fields: fields to be displayed
    * fieldsets: control the layout of admin “add” and “change”
    * filter_horizontal / vertical: better display for ManyToManyField
  ![filter_horizontal](images/20210403_203842.png)
  * SimpleListFilter
    * title: displayed in the right sidebar
    * paramter_name: Parameter for the filter that will be used in the URL query
    * template: html template for custom filter
    * lookups(self, request, model_admin): [(url query, human_readable name), ..]
    * queryset(self, request, queryset)

* django_filters
  * pip install djangorestframework
  * 'django-filter' in INSTALLED_APPS
  * rest_framework.DjangoFilterBackend

```py
from django.contrib import admin
from .models import Author
from django.contrib.admin import SimpleListFilter

from rest_framework.generics import ListAPIView
from django_filters.rest_framework import DjangoFilterBackend

from user.serializers import UserSerializer
from user.models import User


# 1. Simple admin
@admin.register(IceCreamBar)
class IceCreamBarModelAdmin(admin.ModelAdmin):
  list_display = ('name', 'shell', 'filling')
  readonly_fields = ('show_url',)
  def show_url(self, instance):
    url = reverse('ice_cream_bar_detail', kwargs={'pk': instance.pk})
    response = format_html("""<a href="{0}">{0}</a>""", url)
    return response
  show_url.short_description = 'Ice Cream Bar URL' # Displays HTML tags
  show_url.allow_tags = True # Never set allow_tags to True against user submitted data!!!

# 2. Custom filter
class CountryFilter(SimpleListFilter):
  title = 'country' # or use _('country') for translated title
  parameter_name = 'country'

  def lookups(self, request, model_admin):
    countries = set([c.country for c in model_admin.model.objects.all()])
    return [(c.id, c.name) for c in countries] + [('AFRICA', 'AFRICA - ALL')]

  def queryset(self, request, queryset):
    if self.value() == 'AFRICA':
      return queryset.filter(country__continent='Africa')
    if self.value():
      return queryset.filter(country__id__exact=self.value())

class CityAdmin(ModelAdmin):
  list_filter = (CountryFilter,)

# 3. Admin View
""" api_views.py """
class UserList(ListAPIView):
  queryset = User.objects.all()
  serializer_class = UserSerializer
  filter_backends = (DjangoFilterBackend,)
  filter_fields = ("team_id")
```

{% endtab %}
{% endtabs %}

## Authentication

{% tabs %}
{% tab title='python' %}

* django
  * admin
    * UserAdmin
  * get_user_model(): attempt to retrieve the model class at the moment your app is imported the first time
  * models
    * AbstractUser: Replace auth User with custom
      * USERNAME_FIELD: overwrite user (ex: email)
      * REQUIRED_FIELDS: required using createsuperuser (ex: ['date_of_birth'])
      * EMAIL_FIELD: A string describing the name of the email field on the User model
  * User
    * check_password(raw_password): Returns True if the given raw string is the correct password for the user
    * set_password(raw_password): taking care of the password hashing
    * get_all_permissions(obj=None): Returns a set of permission strings that the user has, both through group and user permissions
  * models.AnonymousUser: a class that implements django.contrib.auth.models.User interface, with these differences:
  * mixins
    * LoginRequiredMixin
      * permission_classes: control

```py
from .models import Article
from .serializers import ArticleSerializer
from rest_framework import generics
from rest_framework import mixins
from rest_framework.authentication import SessionAuthentication,TokenAuthentication, BasicAuthentication
from rest_framework.permissions import IsAuthenticated

# 1. Replace with custom User in settings.py
AUTH_USER_MODEL = 'YourAppName.YourClassName'

# 2. Remove default field in AbstractUser
first_name = None
last_name = None

# 3. Create Superuser
admin_emails = os.environ.get("DJANGO_ADMIN_EMAILS").split(",")
admin_pws = os.environ.get("DJANGO_ADMIN_PASSWORDS").split(",")

for admin_email, admin_pw in zip(admin_emails, admin_pws):
  if not User.objects.filter(email=admin_email).exists():
    user = User(email=admin_email, is_staff=True, is_superuser=True, is_active=True)
    user.set_password(admin_pw)
    user.save()
    logging.info("Created : %s", user)
  else:
    logging.info("User already Exists")

# 4. DRF
class GenericAPIView(generics.GenericAPIView, mixins.ListModelMixin, mixins.CreateModelMixin,
                    mixins.UpdateModelMixin, mixins.RetrieveModelMixin, mixins.DestroyModelMixin):
  serializer_class = ArticleSerializer
  queryset = Article.objects.all()
  lookup_field = 'id'

  authentication_classes = [SessionAuthentication, BasicAuthentication]
  #authentication_classes = [TokenAuthentication]
  permission_classes = [IsAuthenticated]

  def get(self, request, id = None):
    if id:
      return self.retrieve(request)
    else:
      return self.list(request)

  def post(self, request):
    return self.create(request)

  def put(self, request, id=None):
    return self.update(request, id)

  def delete(self, request, id):
    return self.destroy(request, id)
```

{% endtab %}
{% endtabs %}

## Generics

* CreateAPIView
* ListAPIView
* RetrieveUpdateDestroyAPIView
* UpdateAPIView

![View class diagrams](images/20210408_010144.png)

```py
from rest_framework import generics

# 1. View
class TaskUpdateView(generics.UpdateAPIView):
  lookup_field = "id"
  serializer_class = TaskSerializer

  def get_queryset(self):
    return Task.objects.filter(
      project__id=self.kwargs["project_id"], id=self.kwargs["id"],)

class ListTask(generics.ListCreateAPIView):
  queryset = models.Todo.objects.all()
  serializer_class = TodoSerializer

urlpatterns = [
  url(r"^project/(?P<project_id>[^/]+)/task/(?P<id>[^/]+)$",
      TaskUpdateView.as_view(), name="project-task-update",),
]
```

## Renderers

* JSONRenderer
  * render(`serializer`.data)
* LimitOffsetPagination

```py
# urls.py
from django.urls import path, include
from .views import ArticleViewSet
from rest_framework.routers import DefaultRouter

router = DefaultRouter()
router.register('article', ArticleViewSet, basename='article')

urlpatterns = [
  path('viewset/', include(router.urls))
]
```

### Nest

* [drf-nested-routers](https://github.com/alanjds/drf-nested-routers)
* pip install drf-nested-routers

> Method

* register
  * basename: need to explicitly set the basename argument when registering the viewset with get_queryset()

```py
# /domain/ <- Domains list
# /domain/{pk}/ <- One domain, from {pk}
# /domain/{domain_pk}/nameservers/ <- Nameservers of domain from {domain_pk}
# /domain/{domain_pk}/nameservers/{pk} <- Specific nameserver from {pk}, of domain from {domain_pk}

# urls.py
from rest_framework_nested import routers
from views import DomainViewSet, NameserverViewSet
(...)

router = routers.SimpleRouter()
router.register(r'domains', DomainViewSet)

domains_router = routers.NestedSimpleRouter(router, r'domains', lookup='domain')
domains_router.register(r'nameservers', NameserverViewSet, basename='domain-nameservers')

# 'basename' is optional. Needed only if the same viewset is registered more than once
# Official DRF docs on this option: http://www.django-rest-framework.org/api-guide/routers/
urlpatterns = patterns('',
  url(r'^', include(router.urls)),
  url(r'^', include(domains_router.urls)),
)

# views.py
## For Django' ORM-based resources ##
class NameserverViewSet(viewsets.ModelViewSet):
  def get_queryset(self):
    return Nameserver.objects.filter(domain=self.kwargs['domain_pk'])

## OR: non-ORM resources ##
class NameserverViewSet(viewsets.ViewSet):
  def list(self, request, domain_pk=None):
    nameservers = self.queryset.filter(domain=domain_pk)
    (...)
    return Response([...])

  def retrieve(self, request, pk=None, domain_pk=None):
    nameservers = self.queryset.get(pk=pk, domain=domain_pk)
    (...)
    return Response(serializer.data)
```

## Serializer

* Any database schema change may invalidate the serialized data

![Serializer diagram](images/20210408_010304.png)

* BaseSerializer: easily support alternative serialization and deserialization styles
  * \__cls__(`instance`): Serialize `instance`
    * many=True: create multiple data
  * errors: Returns any errors during validation
  * data: the outgoing primitive representation
  * validated_data: the validated incoming data
  * is_valid(): Deserializes and validates incoming data
    * raise_exception=True: throw serializers.ValidationError when validation errors
  * save(): Persists the validated data into an object instance

* Serializer: allow querysets / model instances to be converted to native Python data easily rendered into JSON, XML
  * [-] must redefine all the fields

* HyperlinkedModelSerializer: uses hyperlinks to represent relationships, rather primary keys

* ListSerializer: provides the behavior for serializing and validating multiple objects at once
  * many=True when instantiating serializer

* ModelSerializer: automatically create a Serializer class with fields that correspond to the Model fields
  * Meta
    * depth = `depth`: nested serialization up to `depth`
    * extra_kwargs = `{'password': {'write_only': True}}`
    * fields = [`*fields`]: Only serilize `*fields` for all fields use \__all__
    * read_only_fields
    * model=`model`: set to `model` class

{% tabs %}
{% tab title='python' %}

* pickle
  * dump(obj, file)
  * load(file)

```py
from rest_framework import serializers
from rest_framework import serializers

# 1. Basic serializer
class CommentSerializer(serializers.Serializer):
  email = serializers.EmailField()
  content = serializers.CharField(max_length=200)
  created = serializers.DateTimeField()
  def create(self, validated_data):
    return Comment.objects.create(**validated_data)

  def update(self, instance, validated_data):
    instance.email = validated_data.get('email', instance.email)
    instance.content = validated_data.get('content', instance.content)
    instance.created = validated_data.get('created', instance.created)
    instance.save()
    return instance

serializer = CommentSerializer(comment)       # json serializer.data
json = JSONRenderer().render(serializer.data) # binary string

# 2. List Serializer
class BookListSerializer(serializers.ListSerializer):
  def create(self, validated_data):
    books = [Book(**item) for item in validated_data]
    return Book.objects.bulk_create(books)

class BookSerializer(serializers.Serializer):
  class Meta:
    list_serializer_class = BookListSerializer

# Create a model serializer
class GeeksSerializer(serializers.ModelSerializer):
  # specify model and fields
  class Meta:
    model = Book
    fields = ('title', 'description')
```

{% endtab %}
{% endtabs %}

## Swagger

* pip install -U drf-yasg

```py
# settings.py
INSTALLED_APPS = [
   ...
   'django.contrib.staticfiles',  # required for serving swagger ui's css/js files
   'drf_yasg',
   ...
]
```

## Parsers

* JSONParser
  * parse(`io_stream`): convery back to json

## DRF utils

* swagger_auto_schema
  * request_body
  * responses
  * deprecated

## Views

* [Reference](https://www.youtube.com/watch?v=B38aDwUpcFc)
* ModelViewSet: built-in implement basic actions as list, retrieve, create, update or destroy
* GenericViewSet: doesn't provide any implementations of basic actions

{% tabs %}
{% tab title='views.py' %}

```py
from .models import Article
from .serializers import ArticleSerializer
from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework.decorators import api_view
from rest_framework import status

# 1. Function based view
@csrf_exempt
def article_list(request):
  if request.method == 'GET':
    articles = Article.objects.all()
    serializer = ArticleSerializer(articles, many=True)
    return JsonResponse(serializer.data, safe=False)

  elif request.method == 'POST':
    data = JSONParser().parse(request)
    serializer = ArticleSerializer(data=data)
    if serializer.is_valid():
      serializer.save()
      return JsonResponse(serializer.data, status=201)
    return JsonResponse(serializer.errors, status=400)

@csrf_exempt
def article_detail(request, pk):
  try:
    article = Article.objects.get(pk=pk)
  except Article.DoesNotExist:
    return HttpResponse(status=404)

  if request.method == 'GET':
    serializer = ArticleSerializer(article)
    return JsonResponse(serializer.data)

  elif request.method == 'PUT':
    data = JSONParser().parse(request)
    serializer = ArticleSerializer(article, data=data)
    if serializer.is_valid():
      serializer.save()
      return JsonResponse(serializer.data)
    return JsonResponse(serializer.errors, status=400)

  elif request.method == 'DELETE':
    article.delete()
    return HttpResponse(status=204)

# 2. View using @api_view
@api_view(['GET', 'POST'])
def article_list(request):
  if request.method == 'GET':
    articles = Article.objects.all()
    serializer = ArticleSerializer(articles, many=True)
    return Response(serializer.data)
  elif request.method == 'POST':
    serializer = ArticleSerializer(data=request.data)
    if serializer.is_valid():
      serializer.save()
      return Response(serializer.data, status=status.HTTP_201_CREATED)
    return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

@api_view(['GET', 'PUT', 'DELETE'])
def article_detail(request, pk):
  try:
    article = Article.objects.get(pk=pk)
  except Article.DoesNotExist:
    return Response(status=status.HTTP_404_NOT_FOUND)

  if request.method == 'GET':
    serializer = ArticleSerializer(article)
    return Response(serializer.data)
  elif request.method == 'PUT':
    serializer = ArticleSerializer(article, data=request.data)
    if serializer.is_valid():
      serializer.save()
      return Response(serializer.data)
    return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

  elif request.method == 'DELETE':
    article.delete()
    return Response(status=status.HTTP_204_NO_CONTENT)
```

{% endtab %}
{% tab title='urls.py' %}

```py
from django.contrib import admin
from django.urls import path, include

urlpatterns = [
  path('admin/', admin.site.urls),
  path('', include('api_basic.urls'))
]
```

{% endtab %}
{% endtabs %}

### View Class

{% tabs %}
{% tab title='python' %}

```py
# 1. Class based view
### Views.py
class ArticleAPIView(APIView):
  def get(self, request):
    articles = Article.objects.all()
    serializer = ArticleSerializer(articles, many=True)
    return Response(serializer.data)

  def post(self, request):
    serializer = ArticleSerializer(data=request.data)
    if serializer.is_valid():
      serializer.save()
      return Response(serializer.data, status=status.HTTP_201_CREATED)
    return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

class ArticleDetails(APIView):
  def get_object(self, id):
    try:
      return Article.objects.get(id=id)
    except Article.DoesNotExist:
      return Response(status=status.HTTP_404_NOT_FOUND)

  def get(self, request, id):
    article = self.get_object(id)
    serializer = ArticleSerializer(article)
    return Response(serializer.data)

  def put(self, request,id):
    article = self.get_object(id)
    serializer = ArticleSerializer(article, data=request.data)
    if serializer.is_valid():
      serializer.save()
      return Response(serializer.data)
    return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

  def delete(self, request, id):
    article = self.get_object(id)
    article.delete()
    return Response(status=status.HTTP_204_NO_CONTENT)

### Urls.py
from django.urls import path
from .views import ArticleAPIView, ArticleDetails

urlpatterns = [
  path('article/', ArticleAPIView.as_view()),
  path('detail/<int:id>/', ArticleDetails.as_view()),
]
```

{% endtab %}
{% endtabs %}

## NoSQL

* horizontally scalable, add servers in NoSQL database infrastructure to handle more traffic
* Flexible Schema: NoSQL support key-value structures which can be added as needed
* Distributed Data: Parallel read, write across multiple servers, incremental growth in cluster
* Replication: saving multiple copies of data single copies of data create bottlenecks (tune)
* Eventual consistency

* Nested: Three recently visited chat
  * [+] Simple, Esay
  * [-] Not scalable
* Subcollections: Create users within chat
  * [+] Size of parent is same
  * [-] Hard to delete subcollection
* Root-level collections
  * [+] N to N relation one for users and another for rooms and messages
  * [-] Getting data that is naturally hierarchical increase complexity

* wide column: Have column families, which are containers for rows
  * Don’t need to know all the columns and row doesn’t have to have the same # of columns
  * [+] Best suited for analyzing large datasets
  * [ex] Cassandra, HBase
  ![wide column](images/20210220_191640.png)

* Graph: Store data whose relations are best represented in a graph
  * Data is saved in graph with nodes (entities), properties (information), lines (connections)
  * Neo4J
  * solr: distributed indexing, replication, load-balanced querying, automated failover, recovery, centralized config
    * powers the search and navigation features

## Key-Value Stores

* Data is stored in an array of key-value pairs
* key is an attribute name which is linked to a ‘value’
* [+]caching

* Redis: In-memory key-value database with optional durability
  * keys may have internal structure and expiry (captcha images)
  * ziplist compacts size of list in memory without changing contents
  * more complex for insertion and deletion
  * support abstract data structure → str, list, map, set, sorted set, HyperLogLog, bitmap, stream, spatial index
  * replication is accomplished through master-slave mode

### Elastic Search

| SQL      | elasticsearch         |
| -------- | --------------------- |
| Database | Index                 |
| Table    | Type                  |
| Row      | Document              |
| Column   | Field                 |
| Schema   | Mapping               |
| Index    | Everything is indexed |
| SQL      | Query DSL             |

> Terms

* Cluster

![Clusters](images/20210205_165935.png)

* Documents: For single customer or order or an event resides in index
* Nodes: Part of the cluster that stores the data with search and index capabilities
  * Node names are lower-case and can have many of them

* Shard, Replica: portion of the index
* Indexes: Collection of similar documents

> Types

* category or partition of index

```text
<REST verb> <Index> <Type> <ID>
```

### Firebase

{% tabs %}
{% tab title='javascript' %}

```js
const functions = require("firebase-functions");
const admin = require("firebase-admin");

admin.initializeApp();
const express = require("express");
const app = express();

app.get("/screams", (req, res) => {
  admin.firestore().collection("spots").get()
    .then(data => {
      let screams = [];
      data.forEach(doc => {
        screams.push(doc.data());
      });
      return res.json(screams);
    })
    .catch(err => console.error(err));
});

app.post("/scream", (req, res) => {
  const newScream = {
    body: req.body.body,
    userHandle: req.body.userHandle,
    createdAt: admin.firestore.Timestamp.fromDate(new Date())
  };

  admin.firestore().collection("spots").add(newScream)
    .then(doc => {
      res.json({
        message: `document ${doc.id} created successfully`
      });
    })
    .catch(err => {
      res.status(500).json({
        error: "something went wrong"
      });
    });
});

exports.api = functions.https.onRequest(app);
```

{% endtab %}
{% tab title='python' %}

* Transactions: a set of read and write operations on one or more documents
* Batched Writes: a set of write operations on one or more documents (max 500)
* firestore.Increment(50): if current isn’t numeric value, sets field to the given value
* doc_ref.update({'id': firestore.DELETE_FIELD})  # delete field
* city_ref.update({u'regions': firestore.ArrayRemove([u'east_coast'])})    # delete from array

* Client
  * collection("user"): CollectionReference
  * document("doc"): DocumentReference

* WriteBatch

* CollectionReference
  * db.collection("problem"): get reference
  * list_documents() → Generator[DocRef]: list documents
  * stream()  → Generator[DocSnap]: list streams
  * get(): get all documents in collection
  * delete()

* DocumentReference
  * id: id
  * document("rbtmd1010")
  * get() → DocumentSnapShot(): get_document
  * delete(): delete document
  * update({"kr_name": '황규승'}): update document

* DocumentSnapshot
  * to_dict(): convert to dictioanry

```py
from firebase_admin import credentials, firestore, initialize_app
from collections import defaultdict
from functools import lru_cache
from itertools import islice

# 1. Batch Usage
batch = db.batch() # Write in patch
nyc_ref = db.collection(u'cities').document(u'NYC') # Set the data for NYC
batch.set(nyc_ref, {u'name': u'New York City'})

sf_ref = db.collection(u'cities').document(u'SF')   # Update the population for SF
batch.update(sf_ref, {u'population': 1000000})
den_ref = db.collection(u'cities').document(u'DEN') # Delete DEN
batch.delete(den_ref)
batch.commit()    # Commit the batch

# 2. Firebas class
class FirebaseDB():
  def __init__(self):
    cred = credentials.Certificate(service_account_credential)
    try:
      initialize_app(cred)
    except Exception as e:
      logger.error(e)
      return
    self._db = firestore.client()

  def add(self, collection_id, document, overwrite=True):
    document_id = document.__dict__[collection_id + "_id"]
    document_ref = self._db.collection(collection_id).document(document_id)

    if not overwrite and document_ref.get().exists:
      return False
    document_ref.set(document.__dict__)
    return True

  def delete(self, collection_id, document_id, ignore_missing=True):
    logger.debug(f"delete({collection_id}, {document_id})")

    document_ref = self._db.collection(collection_id).document(document_id)
    if not ignore_missing and not document_ref.get().exists:
      return False
    document_ref.delete()
    return True

  @functools.lru_cache
  def get_all(self, collection_id):
    logger.debug(f"get_all({collection_id})")
    return {doc_ref.id: dict2class(collection_id, doc_ref.to_dict())
            for doc_ref in self._db.collection(collection_id).get()}

  def get(self, collection_id, document_ids):
    document_id2obj = self.get_all(collection_id)
    documents = []
    if not isinstance(document_ids, list):
      document_ids = [document_ids]
    for document_id in document_ids:
      documents.append(document_id2obj[document_id])
    return documents[0] if len(documents) == 1 else documents

remote_db = FirebaseDB()

# 3. update_solved.py
class Team:
  def __init__(self, team_id="", admin_ids=None, member_ids=None):
    self.team_id = team_id
    self.admin_ids = admin_ids or []
    self.member_ids = member_ids or []

  @staticmethod
  @lru_cache
  def show_progress(team_id):
    from ..database import local_db, remote_db
    member_ids = remote_db.get("team", team_id).member_ids
    members = remote_db.get("member", member_ids)
    members.sort(key=lambda member: len(member.solved_problem_ids))
    html = '<div id="search-problem" onchange=toggle_visibility()>'
    html += 'bj_range=<input type="number" class="min_bj_level" value="1">~ \
                      <input type="number" class="max_bj_level" value="10"><br>'

    for i, member in enumerate(reversed(members)):
      html += f'<input id="{member.id}" class="show_member_id" type="checkbox">{member.kr_name} \
        {len(member.solved_problem_ids)} {member.baekjoon_id}</input><br>'
      member.solved_problem_ids = set(member.solved_problem_ids)

    problems = local_db.get_all("problem")
    problems = problems.values()
    cate2problems = defaultdict(list)
    for problem in problems:    # cache headers to problem for effeciency
      if problem.solution_link != "" and problem.problem_id.startswith("BJ"):
        cate2problems[f"{problem.category_id}"].append(problem)
    for category in categories:
      html += f"<h1>{category}</h1>"
      for problem in sorted(cate2problems[f"{category}"], key=lambda problem: problem.level):
        html += f'<table style="table-layout:fixed;">'
        html += f"<tr id='{problem.level}' class='bj_level'>"
        html += f"<td style='width:400px;'>{problem.link}</td>"
        html += f"<td style='width:70px;'>{problem.solution_link}</td>"
        html += " ".join([f"<td> <span id={member.id} class= \
          '{'' if problem.problem_id in member.solved_problem_ids else 'member_id'}' \
          style='display:none;'>{member.kr_name}</span></td>" for member in members])
        html += f"</tr>"
      html += f"</table>"
    html += "</div>"
    return html

for member_ref in db.collection("member").list_documents():
  member = member_ref.get().to_dict()
  member_ref.update({'solved_problem_ids': member["solved"], 'solved': firestore.DELETE_FIELD})
```

{% endtab %}
{% endtabs %}

### Mongo DB

![mongo db](images/20210220_192135.png)

```sh
systemctl start mongod   # start mongodb
systemctl status mongod  # show mongodb status

/etc/mongod.conf     # configuration
/data/db             # default dbpath
/var/lib/mongo       # data directory
/var/log/mongodb     # log directory

27017                # default port for mongod and mongos instances
27018                # when running with --shardsvr command-line option
27019                # when running with --configsvr command-line option
```

* mongod CLI
  * help: Show help
  * --repair: repair
  * show dbs: Print a list of all databases on the server
  * use `db`: Switch current database to `db`
  * db.help(): Show help for database methods
  * --dbpath arg: Directory for datafiles defaults to /data/db
  * db.`collection`.help(): help on collection methods. collection can be non-existing
  * show collections: Print a list of all collections for current database

### Spark

* Driver Program creates Resilient distributed datasets (RDDs)
* Low-latency for small micro-batch size
* Batch and stream processing using disk or memory storage
* SparkSQL, Spark streaming, MLlib, GraphX

* Commands
  * lazy evaluation → transformations are not executed until the action stage
  * Narrow: processing logic depends only on data, residing in the partition → no data shuffling necessary
  * Wide: transformation that requires data shuffling across node partitions

* Function
  * collect(): copy all elements to the driver
  * take(n): copy first n elements
  * reduce(func): aggregate elements with func
  * saveAsTextFile(filename): Save to local file or HDFS

* Narrow Transformation
  * coalesce(): reduce number of partitions
  * filter(func): keep only elements where function is true
  * flatMap(func): map then aggregate
  * map(func): apply function to each element of RDD

* Wide Transformation
  * groupbykey
  * reducebykey

* MLlib

* GraphX
  * Uses property graph model → both nodes and edges can have attributes and values
  * triplet view → logically joins vortex and edge properties

{% tabs %}
{% tab title='python' %}

```py
import pyspark
from operator import add
from pyspark.mllib.stat import Statistics

# 1. Reduce
sc = pyspark.SparkContext.getOrCreate()
data = sc.parallelize (["scala", "hadoop", "spark", "akka", "spark vs hadoop", "pyspark", "pyspark and spark"])
print(data.count())
print("data.collect()")
filtered = data.filter(lambda x: 'spark' in x).collect()
print(filtered)
print(data.reduce(add))
file = sc.textFile('00_keywords.py')
print(f"{file.count()}")
print(f"{file.take(3)}")
print(f"{file.filter(lambda s: 'print' in s.lower()).count()}")
spark = pyspark.sql.SparkSession(sc)
files = sc.wholeTextFiles('.')
pprint(f"{files.count()}")
df = files.toDF(['name', 'data'])
print(f"{df.select('name').toPandas().head()}")
spark.read.csv('competition_vision/mnist/data/mnist_train.csv').toPandas()
spark.read.load('competition_vision/mnist/data/mnist_train.csv').head()

# 2. MLlib
dataMatrix = sc.parallelize([[1,2,3],[4,5,6], [7,8,9],[10, 11, 12]])
summary = Statistics.colStats(dataMatrix)

from pyspark.mllib.clustering import KMeans, KMeansModel
import numpy as np
data = sc.textFile("data.txt")
parsedData = data.map(lambda line: np.array([float(x) for x in line.split(' ')]))
clusters = Kmeans.train(parsedData, k=3)
```

{% endtab %}
{% endtabs %}

### Splunk

* Real-time log forwarding | syslog analysis | server monitoring | alerts, notification

![Splunk](images/20210225_180230.png)

* command

```sh
# return the average population of the counties in Georgia
source="census.csv" CTYNAME != "Georgia" STNAME="Georgia" | stats mean(CENSUS2010POP)

# state with the most counties
source="census.csv" | stats count by STNAME | sort count desc
```

## Hadoop

![Hadoop](images/20210205_170217.png)

* Open-source data storage framework that store and process large data sets in parallel and distributed fashion
* Scalability commodity hardware for data storage, availability commodity hardware for distributed processing
* JVMs do not share state, processes differ between Hadoop 1.0 and 2.0
* Hadoop cluster
* Default chunk size, the size of each piece of a file is 64 megabytes
* hadoop fs -copyFromLocal words.txt
* copy into hadoop
* One replica on local node, Second / third replica on a remoate rack, Additional replicas are randomly placed
  * Clients read from nearest replica, would like to make this policy pluggable
* vs HBase: HBase is NoSQL, hadoop uses an alternative file system (HDFS)
* [+] Long term availability of data, future anticipated data growth
* [+] Many platforms over single data store (facilitate shared environment)
* [+] High volume, variety, behavioral data → batch process, health care
* [+] Pre-built hadoop images → quick prototyping, deploying, and validating of projects
* [-] Small data processing, Task level parallelism, Random data access
* [-] Advanced algorithms (highly coupled data processing algorithm)
* [-] Replacement to your infrastructure (may not be suitable solution for business case)
* [-] Machine learning → HDFS Bottleneck | Mapreduce Computation | No interactive shell | Java
* [-] Line of Business → usually transactional and not a good fit (X - use relational database)
* [ex] commercial distribution: Cloudera, Hortonworks, MapR
* [ex] Open source: apache, public cloud: Iaas(VM, docker), PaaS(AWS, HDinsight), some commercial available

> Terms

* Checkpointing: process of combining edit logs with FsImage, happens periodically (default: 1 hour)

* Cluster: designed specifically for storing and analyzing huge unstructured data in distributed computing environment
  * Such clusters run Hadoop's open source distributed processing software on low-cost commodity computers
  * 40 nodes/rack, 1-4000 nodes in cluster
  * 1 Gbps bandwidth within rack, 8 Gbps out of rack
  ![Clusters](images/20210607_222626.png)
  ![Hadoop cluster](images/20210607_230709.png)

* DataNode: Serves read / write requests of data / meta-data to clients
  * Slave daemons, Stores actual data
  * Facilitates pipelining of data (forwards data to other specified DataNodes)
  * Block server: stores data in local file system (ext3), meta-data of a block (CRC)
  * Block report: periodically sends a report of an existing blocks to NameNode

* editLog: only contain the most recent changes
  * reside in the RAM of the machine

* fsImage: contain all the details of all the changes

* NameNode: Maintains and manages DataNodes, one per cluster
  * records metadata (data blocks info, location of blocks stored, the size of files, permissions, hierarchy) in memory
  * No demand paging of meta-data
  ![HDFS](images/20210607_223905.png)

* Rebalancer: \% disk full on DataNodes should be similar
  * Usually run when new DataNodes are added
  * Cluster is online when Rebalancer is active
  * throttled to avoid network congestion
  ![Rebalancer](images/20210607_230133.png)

* Secondary NameNode: Allows faster Failover as it prevents edit logs from getting too huge
  * Takes over the responsibility of checkpointing, therefore, making NameNode more available

* fs
  * hadoop fs -`command_name`
  * copyFromLocal `fname`
  * copyToLocal `fname`

* jar
  * wordcount `ins` `out`
  * hadoop jar |usr|jars|hadoop-examples.jar wordcount

* Yarn: Flexible scheduling and resource management
  * Allows various applications to run on the same Hadoop cluster

* HDFS (Hadoop distributed file system)
  * Maintains three copies of every block
  * Single namespace for entire cluster, metadata (file names, block, locations)
  * Files are append-only split into 128mb blocks
  * Block replicated across several datanodes
  * Optimized for large files (10k nodes, 100m files, 10PB), batch processings, sequential reads
    * Data locations exposed so that computations can move to where data resides
    * provides very high aggregate bandwidth
  * Assumes commodity hardware: files are replicated to handle hardware failure
    * Detect failures and recovers from them
  * User space, runs on heterogeneous OS
  ![HDFS](images/20210607_224621.png)

* Hive: Hadoop subproject in SQL manner when files are insufficient, need tables, schemas, partitions, indices
  * Need a multi petabyte warehous for an open data format (RDBMS)

> Question

* Challenges
  1. Chaep nodes fails, especially if you have many
      * Build fault tolerance into system
  1. Commodity network = low bandwidth
      * Push computation to the data
  1. Programming distributed systems is hard
      * Data parallel programming models (users write map & reduce functions, system distributes work and handles faults)
      * Use CRC32 checksum to validate data

* Three layers of ecosystem?
  * Data Management and Storage
  * Data Integration and Processing
  * Coordination and Workflow Management

### Mapreduce

![Map Reduce](images/20210607_224939.png)

* Large data processing API designed for scalability and fault-tolerance
  * Retry on another node: OK for a map because no dependencies, for reduce because map outputs are on disk
  * If same task fails repeatedly, fail job or ignore that input block
* Pluggable user code runs in generic framwork
* Dependent tasks, interactive analysis, Native support for Java only
* High-latency, allow parallel & distributed processing using disk storage
  * Launch second copy of task if task is slow then kill when finishes first
* Map-Reduce consists of three main steps: Mapping, Shuffling and Reducing
* Map: Apply same operation to each member of collection
  * minimize network usage by saving outputs to local disk before serving them to reducers
  * allows recovery if a reducer crashses, hvaing more reducers than nodes
* Reduce: collecting things that have same 'key'
* [+] Hides complexities of parallel programming  → search engine page ranking and topic mapping
* [-] frequently changing data → slow, as it reads entire input data
* [ex] Index construction G search, Article clustering for G News, Machine translation, FB Spam detection
* [ex] Log processing, web search indexing, ad-hoc queries

* Design pattern
  * wc, cat \*, grep, sort, unique, cat > file, input, map, shuffle, reduce, output

```py
def mapper(line):
  for word in line.split():
    output(word, 1)

def reducer(key, values):
  output(key, sum(values))
```

### Migration

{% tabs %}
{% tab title='python' %}

* django.migrations
  * CreateModel
  * AddField

{% endtab %}
{% endtabs %}

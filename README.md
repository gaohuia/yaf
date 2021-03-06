# Yaf - Yet Another Framework  
[![Build Status](https://secure.travis-ci.org/laruence/yaf.png)](https://travis-ci.org/laruence/yaf)

PHP framework written in c and built as a PHP extension. Forked from Laruence's yaf.

Here is some difference with Laruence's Yaf.

* Controller class in default module must be in a namespace `app\controllers` when `use_namespace` is On;
* Controller class in none default module must be in a namespace `app\modules\[Module]\controllers` when `use_namespace` is On; In which `[Module]` is your module name
* Bootstrip class must be in namespace `app` when `use_namespace` is On;
* `name_suffix` will be ignored when `use_namespace` is On;

In another words, you can write controllers like this.
```php

<?php

namespace app\controllers;     

class Ns extends \Yaf\Controller_Abstract 
{
    public function testAction()    
    { 
        echo 'hello';          
    }
}
```

Or like this if your are writting controllers in a none default module.

```php
<?php

namespace app\modules\Api\controllers;

use core\controllers\WebController;

class Passport extends WebController
{
    public function loginAction()
    {   
        echo 'login ok';
    }
}
```


## Requirement
- PHP 5.2 +

## Install

### Compile Yaf in Linux
```
$/path/to/phpize
$./configure --with-php-config=/path/to/php-config
$make && make install
```

## Document
Yaf manual could be found at: http://www.php.net/manual/en/book.yaf.php

## IRC
efnet.org #php.yaf

## For IDE
You could find a documented prototype script here: https://github.com/elad-yosifon/php-yaf-doc

## Tutorial

### layout
A classic application directory layout:

```
- .htaccess // Rewrite rules
+ public
  | - index.php // Application entry
  | + css
  | + js
  | + img
+ conf
  | - application.ini // Configure 
- application/
  - Bootstrap.php   // Bootstrap
  + controllers
     - Index.php // Default controller
  + views    
     |+ index   
        - index.phtml // View template for default controller
  - library
  - models  // Models
  - plugins // Plugins
```
### DocumentRoot
You should set `DocumentRoot` to `application/public`, thus only the public folder can be accessed by user

### index.php
`index.php` in the public directory is the only way in of the application, you should rewrite all request to it(you can use `.htaccess` in Apache+php mod) 

```php
<?php
define("APPLICATION_PATH",  dirname(dirname(__FILE__)));

$app  = new Yaf_Application(APPLICATION_PATH . "/conf/application.ini");
$app->bootstrap() //call bootstrap methods defined in Bootstrap.php
    ->run();
```
### Rewrite rules

#### Apache

```conf
#.htaccess
RewriteEngine On
RewriteCond %{REQUEST_FILENAME} !-f
RewriteRule .* index.php
```

#### Nginx

```
server {
  listen ****;
  server_name  domain.com;
  root   document_root;
  index  index.php index.html index.htm;
 
  if (!-e $request_filename) {
    rewrite ^/(.*)  /index.php/$1 last;
  }
}
```

#### Lighttpd

```
$HTTP["host"] =~ "(www.)?domain.com$" {
  url.rewrite = (
     "^/(.+)/?$"  => "/index.php/$1",
  )
}
```

### application.ini
`application.ini` is the application config file
```ini
[product]
;CONSTANTS is supported
application.directory = APPLICATION_PATH "/application/" 
```
Alternatively, you can use a PHP array instead: 
```php
<?php
$config = array(
   "application" => array(
       "directory" => application_path . "/application/",
    ),
);

$app  = new yaf_application($config);
....
  
```
### default controller
In Yaf, the default controller is named `IndexController`:

```php
<?php
class IndexController extends Yaf_Controller_Abstract {
   // default action name
   public function indexAction() {  
        $this->getView()->content = "Hello World";
   }
}
?>
```

###view script
The view script for default controller and default action is in the application/views/index/index.phtml, Yaf provides a simple view engine called "Yaf_View_Simple", which support the view template written in PHP.

```php
<html>
 <head>
   <title>Hello World</title>
 </head>
 <body>
   <?php echo $content; ?>
 </body>
</html>
```

## Run the Applicatioin
  http://www.yourhostname.com/

## Alternative
You can generate the example above by using Yaf Code Generator:  https://github.com/laruence/php-yaf/tree/master/tools/cg

## More
More info could be found at Yaf Manual: http://www.php.net/manual/en/book.yaf.php

<?php

function _uc_epayco_checkout_page() {
  $lang = isset($_REQUEST["lang_checkout"]) ? $_REQUEST["lang_checkout"] : 'es';
  $epaycoButtonImage = ($lang == 'EN') 
    ? 'https://multimedia.epayco.co/epayco-landing/btns/Boton-epayco-color-Ingles.png'
    : 'https://multimedia.epayco.co/epayco-landing/btns/Boton-epayco-color1.png';

  $output = t('ePayco Checkout:');
  $output .= '
  <div id="wrap">
    <div class="oe_structure oe_empty">
      <div class="container" style="text-align: center;">
        <div class="loader-container">
          <div class="loading"></div>
        </div>
        <p style="text-align: center;" class="epayco-title">
          <span class="animated-points" id="loading-payments">Cargando...</span>
          <br/>
          <small class="epayco-subtitle"></small>
        </p>
        <center>
          <a id="btn_epayco" href="#">
            <img src="' . $epaycoButtonImage . '" style="border-width:0px;" />
          </a>
        </center>
        <div id="form-button-container">
          <form>
            <input type="hidden" name="epayco_token" value="' . htmlspecialchars($_REQUEST["epayco_token"]) . '"/>
            <input type="hidden" name="amount" value="' . htmlspecialchars($_REQUEST["amount"]) . '"/>
            <input type="hidden" name="tax" value="' . htmlspecialchars($_REQUEST["tax"]) . '"/>
            <input type="hidden" name="base_tax" value="' . htmlspecialchars($_REQUEST["base_tax"]) . '"/>
            <input type="hidden" name="currency" value="' . htmlspecialchars($_REQUEST["currency"]) . '"/>
            <input type="hidden" name="email" value="' . htmlspecialchars($_REQUEST["email"]) . '"/>
            <input type="hidden" name="firstname" value="' . htmlspecialchars($_REQUEST["firstname"]) . '"/>
            <input type="hidden" name="reference" value="' . htmlspecialchars($_REQUEST["reference"]) . '"/>
            <input type="hidden" name="lang_checkout" value="' . htmlspecialchars($_REQUEST["lang_checkout"]) . '"/>
            <input type="hidden" name="checkout_external" value="' . htmlspecialchars($_REQUEST["checkout_external"]) . '"/>
            <input type="hidden" name="test" value="' . htmlspecialchars($_REQUEST["test"]) . '"/>
            <input type="hidden" name="notify_url" value="' . htmlspecialchars($_REQUEST["notify_url"]) . '"/>
            <input type="hidden" name="return_url" value="' . htmlspecialchars($_REQUEST["return_url"]) . '"/>
            <input type="hidden" name="extra2" value="' . htmlspecialchars($_REQUEST["extra2"]) . '"/>
            <input type="hidden" name="extra3" value="' . htmlspecialchars($_REQUEST["extra3"]) . '"/>
            <input type="hidden" name="extra4" value="' . htmlspecialchars($_REQUEST["extra4"]) . '"/>
            <input type="hidden" name="address" value="' . htmlspecialchars($_REQUEST["address"]) . '"/>
            <input type="hidden" name="description" value="' . htmlspecialchars($_REQUEST["description"]) . '"/>
            <input type="hidden" name="country" value="' . htmlspecialchars($_REQUEST["country"]) . '"/>
            <input type="hidden" name="ip" value="' . htmlspecialchars($_REQUEST["ip"]) . '"/>
            
            <script src="https://epayco-checkout-testing.s3.amazonaws.com/checkout.preprod-v2.j"></script>
            <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
            <script type="text/javascript">
            (async function () {
              let epayco_token = document.getElementsByName("epayco_token")[0].value;
              let amount = document.getElementsByName("amount")[0].value;
              let tax = document.getElementsByName("tax")[0].value;
              let base_tax = document.getElementsByName("base_tax")[0].value;
              let currency = document.getElementsByName("currency")[0].value;
              let email = document.getElementsByName("email")[0].value;
              let firstname = document.getElementsByName("firstname")[0].value;
              let reference = document.getElementsByName("reference")[0].value;
              let lang = document.getElementsByName("lang_checkout")[0].value;
              let checkout_external = document.getElementsByName("checkout_external")[0].value;
              let test = document.getElementsByName("test")[0].value;
              let notify_url = document.getElementsByName("notify_url")[0].value;
              let return_url = document.getElementsByName("return_url")[0].value;
              let extra2 = document.getElementsByName("extra2")[0].value;
              let extra3 = document.getElementsByName("extra3")[0].value;
              let extra4 = document.getElementsByName("extra4")[0].value;
              let address = document.getElementsByName("address")[0].value;
              let description = document.getElementsByName("description")[0].value;
              let country = document.getElementsByName("country")[0].value;
              let ip = document.getElementsByName("ip")[0].value;
              
              var checkout_lang = lang == "es" || lang == "es_CO" ? "es" : "en";
              
              if(checkout_lang == "es"){
                document.getElementById("loading-payments").innerText = "Cargando...";
              } else {
                document.getElementById("loading-payments").innerText = "Loading...";
              }

              var data = {
                checkout_version: "2",
                name: reference.substring(0, 50),
                description: description.substring(0, 50),
                invoice: reference,
                currency: currency.toLowerCase(),
                amount: parseFloat(amount),
                taxBase: parseFloat(base_tax),
                tax: parseFloat(tax),
                taxIco: parseFloat(0),
                country: country,
                lang: checkout_lang,
                confirmation: notify_url,
                response: return_url,
                billing: {
                  name: firstname,
                  address: address,
                  email: email,
                },
                autoclick: true,
                ip: ip,
                test: test.toString() === "true",
                extras: {
                  extra2: extra2,
                  extra3: extra3,
                  extra4: extra4
                },
                extrasEpayco: {
                  extra5: "P32"
                },
                method: "POST",
                autoClick: false,
                methodsDisable: [],
                dues: 1,
                noRedirectOnClose: true,
                forceResponse: false,
                uniqueTransactionPerBill: false,
                config: {}
              };

              var openCheckout = function () {
                var btnPagar = document.getElementById("btn_epayco");
                if (btnPagar) {
                  btnPagar.classList.add("disabled");
                }
                if (localStorage.getItem("invoicePayment") == null) {
                  localStorage.setItem("invoicePayment", data.invoice);
                  makePayment(epayco_token, data, checkout_external == "true");
                } else {
                  if (localStorage.getItem("invoicePayment") != data.invoice) {
                    localStorage.removeItem("invoicePayment");
                    localStorage.setItem("invoicePayment", data.invoice);
                    makePayment(epayco_token, data, checkout_external == "true");
                  } else {
                    makePayment(epayco_token, data, checkout_external == "true");
                  }
                }
              };

              var makePayment = async function (token_epayco, info, external) {
                const headers = { "Content-Type": "application/json" };
                if (token_epayco) {
                  headers["Authorization"] = "Bearer " + token_epayco;
                }
                
                try {
                  const response = await fetch("https://eks-apify-service.epayco.io/payment/session/create", {
                    method: "POST",
                    body: JSON.stringify(info),
                    headers: headers
                  });
                  
                  const responseText = await response.text();
                  
                  if (!response.ok) {
                    throw new Error("HTTP error! status: " + response.status + " - " + responseText);
                  }
                  
                  const session = JSON.parse(responseText);
                  
                  if (session.success && session.data && session.data.sessionId) {
                    const sessionId = session.data.sessionId;
                    localStorage.removeItem("sessionPayment");
                    localStorage.setItem("sessionPayment", sessionId);
                    
                    // Verificar que ePayco checkout esté disponible
                    if (!window.ePayco || !window.ePayco.checkout) {
                      throw new Error("ePayco checkout library not loaded");
                    }
                    
                    const checkout = window.ePayco.checkout.configure({
                      sessionId: sessionId,
                      type: external ? "standard" : "onepage",
                      test: info.test
                    });

                    // Event handlers
                    checkout.onCreated(() => {
                      console.log("Evento cuando se crea el flujo transaccional");
                    });

                    checkout.onErrors(errors => {
                      console.log("Evento que notifica un error en la integración");
                      console.error(errors);
                    });

                    checkout.onClosed(() => {
                      console.log("Evento que notifica cuando se cierra el checkout");
                      var btnPagar = document.getElementById("btn_epayco");
                      if (btnPagar) {
                        btnPagar.classList.remove("disabled");
                      }
                    });
                    
                    if (checkout && typeof checkout.open === "function") {
                      checkout.open();
                    } else {
                      console.error("Error: checkout.open no está disponible");
                      console.log("checkout object:", checkout);
                    }
                  } else {
                    console.error("Error: Respuesta inválida del servidor o sessionId no encontrado.", session);
                    alert("Error al inicializar el checkout. Por favor, inténtelo de nuevo.");
                  }
                } catch (error) {
                  console.error("Error al procesar el pago:", error);
                  alert("Error al procesar el pago: " + error.message);
                } finally {
                  var btnPagar = document.getElementById("btn_epayco");
                  if (btnPagar) {
                    btnPagar.classList.remove("disabled");
                  }
                }
              };

              var btnPagar = document.getElementById("btn_epayco");
              if (btnPagar) {
                btnPagar.addEventListener("click", openCheckout);
              }
              openCheckout();
              
              window.onload = function () {
                document.addEventListener("contextmenu", function (e) {
                  e.preventDefault();
                }, false);
              };
            })();
            </script>
          </form>
        </div>
      </div>
    </div>
  </div>
  ';

  return $output;
}


function _uc_epayco_response_page() {
  global $language;

  $response = array();
  foreach ($_GET as $key => $value) {
    $response[$key] = html_entity_decode($value);
  }
   unset($response['q']);


 $ref_payco=$response['ref_payco'];
 $url = 'https://eks-ms-checkout-transaction-service.epayco.io/validation/v1/reference/'.$ref_payco;
  $ch = curl_init();
  $timeout = 5;
  $user_agent='Mozilla/5.0 (Windows NT 6.1; rv:8.0) Gecko/20100101 Firefox/8.0';
  curl_setopt($ch, CURLOPT_URL, $url);
  curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
  curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, false);
  curl_setopt($ch, CURLOPT_USERAGENT, $user_agent);
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 1);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, $timeout);
  curl_setopt($ch,CURLOPT_TIMEOUT,$timeout);
  curl_setopt($ch,CURLOPT_MAXREDIRS,10);
  $data = curl_exec($ch);
  curl_close($ch);
  $jsonData = json_decode($data, true);

  if (!$jsonData ) {
        throw new Exception(t("Unknown. Please contact with desarollo@epayco.com and/or website administrator for more information"));
    }
    try {
       if(isset($jsonData["status"]) && !$jsonData["status"]){
          drupal_access_denied();
      }
		  $validationData = $jsonData['data'];
		  $ref_payco = $validationData['x_ref_payco'];
		  $uid = $validationData['x_extra1'];
		  $session_id = $validationData['x_extra3'];
		  $order = uc_order_load($validationData['x_extra4']);
		} catch (Exception $e) {
		    echo   $e->getMessage(), "\n";
		     drupal_access_denied();
		}



  if (!uc_epayco_get_txn_type()) {
    watchdog('ePayco', 'Response page (' . $validationData['x_extra4'] . '): ' . serialize($response));
  }


  if (!$order) {
    drupal_set_message(t("Order doesn't exists."), 'error');
    drupal_access_denied();
  }

  if ($session_id != session_id()) {
    drupal_set_message(t("You aren't the owner of this order."), 'error');
    drupal_access_denied();
  }

  $signature2= md5($validationData['x_cust_id_cliente'].'^'.uc_epayco_get_api_key().'^'.$validationData['x_extra4'].'^'.$validationData['x_amount'].'^'.uc_epayco_get_currency());

  $signature = uc_epayco_get_signature($validationData['x_extra4'], $validationData['x_amount'],  $validationData['x_currency_code']);

  if (strtoupper($signature2) != strtoupper($signature)) {
    drupal_set_message(t("Signature doesn't match."), 'error');
    drupal_access_denied();
  }else{

    $watchdog_variables = array(
    '!order_id' => $validationData['x_extra4'],
    '!current_order_status' => $order->order_status,
    '!reference_pol' => check_plain($validationData['x_description']),
    );


      switch ($validationData['x_cod_transaction_state']) {

        case 1: // Payment Received
        $comment = t("Order Completed.") . ' ' . t("ePayco# !reference_pol", $watchdog_variables);
               uc_order_update_status($validationData['x_extra4'], 'completed');
        uc_order_comment_save($validationData['x_extra4'], 0, $comment, 'order', 'completed');
        // uc_order_comment_save($validationData['x_extra4'], 0, $comment, 'order');
        uc_payment_enter($validationData['x_extra4'], 'epayco', $validationData['x_amount'], 0, NULL, $comment);
        uc_cart_empty($validationData['x_extra4']);
        uc_cart_complete_sale($order, FALSE);
        watchdog('ePayco', "Order !order_id completed.ePayco # !reference_pol", $watchdog_variables);
        break;

        case 2: // Canceled
        $comment = t("Order Canceled.") . ' ' . t("ePayco # !reference_pol", $watchdog_variables);
        uc_order_update_status($validationData['x_extra4'], 'canceled');
        uc_order_comment_save($validationData['x_extra4'], 0, $comment, 'order', 'canceled');
        uc_epayco_restore_stock($order);
        watchdog('ePayco', "Order !order_id canceled. ePayco # !reference_pol", $watchdog_variables);
        break;

        case 3: // Pending/Processing
        $comment = t("Processing Order.") . ' ' . t("ePayco # !reference_pol", $watchdog_variables);
        uc_order_update_status($validationData['x_extra4'], 'pending');
        uc_order_comment_save($validationData['x_extra4'], 0, $comment, 'order', 'pending');
        uc_cart_empty($validationData['x_extra4']);
        watchdog('ePayco', "Processing order !order_id. ePayco # !reference_pol", $watchdog_variables);
        break;

        case 4: // Rejected
        $comment = t("Order Rejected.") . ' ' . t("ePayco # !reference_pol", $watchdog_variables);
        uc_order_update_status($validationData['x_extra4'], 'canceled');
        uc_order_comment_save($validationData['x_extra4'], 0, $comment, 'order', 'canceled');
        uc_epayco_restore_stock($order);
        watchdog('ePayco', "Order !order_id rejected. ePayco # !reference_pol", $watchdog_variables);
        break;

        case 6: // Reversada
        $comment = t("Order Rejected.") . ' ' . t("ePayco # !reference_pol", $watchdog_variables);
        uc_order_update_status($validationData['x_extra4'], 'canceled');
        uc_order_comment_save($validationData['x_extra4'], 0, $comment, 'order', 'canceled');
        uc_epayco_restore_stock($order);
        watchdog('ePayco', "Order !order_id rejected. ePayco # !reference_pol", $watchdog_variables);
        break;

        case 7: // Pending/Held
        $comment = t("Processing Order.") . ' ' . t("ePayco # !reference_pol", $watchdog_variables);
        uc_order_update_status($validationData['x_extra4'], 'processing');
        uc_order_comment_save($validationData['x_extra4'], 0, $comment, 'order', 'processing');
        uc_cart_empty($validationData['x_extra4']);
        watchdog('ePayco', "Processing order !order_id. ePayco # !reference_pol", $watchdog_variables);
        break;

        case 8: // Pending/Held
        $comment = t("in checkout Order.") . ' ' . t("ePayco # !reference_pol", $watchdog_variables);
        uc_order_update_status($validationData['x_extra4'], 'in checkout');
        uc_order_comment_save($validationData['x_extra4'], 0, $comment, 'order', 'in checkout');
        uc_cart_empty($validationData['x_extra4']);
        watchdog('ePayco', "Processing order !order_id. ePayco # !reference_pol", $watchdog_variables);
        break;

        case 9: // Expired
        $comment = t("Expired Order.") . ' ' . t("ePayco # !reference_pol", $watchdog_variables);
        uc_order_update_status($validationData['x_extra4'], 'abandoned');
        uc_order_comment_save($validationData['x_extra4'], 0, $comment, 'order', 'abandoned');
        uc_cart_empty($validationData['x_extra4']);
        uc_epayco_restore_stock($order);
        watchdog('ePayco', "Order !order_id rejected. ePayco # !reference_pol", $watchdog_variables);
        break;

        case 10: // Abandoned
        $comment = t("Expired Order.") . ' ' . t("ePayco # !reference_pol", $watchdog_variables);
        uc_order_update_status($validationData['x_extra4'], 'abandoned');
        uc_order_comment_save($validationData['x_extra4'], 0, $comment, 'order', 'abandoned');
        uc_cart_empty($validationData['x_extra4']);
        uc_epayco_restore_stock($order);
        watchdog('ePayco', "Order !order_id rejected. ePayco # !reference_pol", $watchdog_variables);
        break;

        case 11: // Canceled
        $comment = t("Order Canceled.") . ' ' . t("ePayco # !reference_pol", $watchdog_variables);
        uc_order_update_status($validationData['x_extra4'], 'canceled');
        uc_order_comment_save($validationData['x_extra4'], 0, $comment, 'order', 'canceled');
        uc_epayco_restore_stock($order);
        watchdog('ePayco', "Order !order_id canceled. ePayco # !reference_pol", $watchdog_variables);
        break;

        case 12: // Anti fraud
        $comment = t("Order Rejected.") . ' ' . t("ePayco # !reference_pol", $watchdog_variables);
        uc_order_update_status($validationData['x_extra4'], 'canceled');
        uc_order_comment_save($validationData['x_extra4'], 0, $comment, 'order', 'canceled');
        uc_epayco_restore_stock($order);
        watchdog('ePayco', "Order !order_id rejected. ePayco # !reference_pol", $watchdog_variables);
        break;

        default:
        $comment = t("Order Error.") . ' ' . t("ePayco # !reference_pol", $watchdog_variables);
        uc_order_comment_save($validationData['x_extra4'], 0, $comment, 'order', $order->order_status);
        watchdog('ePayco', "Error with order !order_id. ePayco # !reference_pol", $watchdog_variables);

      }

  }

  $variables = array(
    'header' => array('', ''),
    'caption' => '',
    'attributes' => array(),
    'empty' => '',
    'colgroups' => array(),
    'sticky' => FALSE,
    );
//$txn_status = $validationData['x_transaction_state'];
$txn_status=$validationData['x_transaction_state'].' ePayco';
  $order_status = uc_order_status_data($order->order_status, 'title');
  if ($order->order_status == 'in_checkout') {
    $order_status .= ". " . t("The transaction has not been confirmed to the merchant, this takes a few seconds, please wait a moment") . ' ' . t("!reload_link to check if it is updated.", array('!reload_link' => l(t("Reload this page"), 'cart/uc_epayco/response', array('query' => $response))));
  }

  $variables['rows'] = array();

  $variables['rows'][] = array('<strong>' . t('Amount') . '</strong>', uc_epayco_format_price($validationData['x_amount']) . ' (' . $validationData['x_currency_code'] . ')');
  $variables['rows'][] = array('<strong>' . t('Transaction Status') . '</strong>', $txn_status);
  $variables['rows'][] = array('<strong>' . t('Transaction ID') . '</strong>', check_plain($validationData['x_ref_payco']));
  $variables['rows'][] = array('<strong>' . t('Sale Reference') . '</strong>', check_plain($validationData['x_extra4']));

  $variables['rows'][] = array('<strong>' . t('Payment Method') . '</strong>', check_plain('ePayco'));
  $variables['rows'][] = array('<strong>' . t('Order Status') . '</strong>', $validationData['x_response']);
  $variables['rows'][] = array('<strong>' . t('Reference Code') . '</strong>', check_plain($validationData['x_ref_payco']));

  $build['table'] = array('#markup' => theme_table($variables));

  $build['options'] = array('#markup' => l(t("Continue Shopping"), variable_get('uc_continue_shopping_url')));

  return $build;
}

function _uc_epayco_confirmation_page() {
  $response = array();
  foreach ($_POST as $key => $value) {
    $response[$key] = html_entity_decode($value);
  }


  $uid = $response['x_extra1'];
  $session_id = $response['x_extra3'];
  $order = uc_order_load($response['x_extra4']);



  $extra3 = unserialize($response['extra3']);
  $uid =  $response['x_extra1'];
  $order = uc_order_load($response['x_extra4']);

  if (!uc_epayco_get_txn_type()) {
    watchdog('ePayco', 'Confirmation Page (' . $response['x_extra4'] . '): ' . serialize($response));
  }

  $watchdog_variables = array(
    '!order_id' => $response['x_extra4'],
    '!current_order_status' => $order->order_status,
    '!reference_pol' => check_plain($response['x_description']),
    );


  if ($response['x_extra4']) {

      $signature=hash('sha256',
        uc_epayco_get_merchant_id().'^'
      .uc_epayco_get_p_key().'^'
      .$response['x_ref_payco'].'^'
      .$response['x_transaction_id'].'^'
      .$response['x_amount'].'^'
      .$response['x_currency_code']
    );

    if (strtoupper($response['x_signature']) == strtoupper($signature)) {
      if (!in_array($order->order_status, array('in_checkout'))) {
        watchdog('ePayco', "Confirming order !order_id but it isn't in checkout. Its current status is !current_order_status.", $watchdog_variables, WATCHDOG_WARNING);
        uc_order_comment_save($response['x_extra4'], 0, t("Confirming order !order_id but it isn't in checkout. Its current status is !current_order_status.", $watchdog_variables));
      }
      if (in_array($order->order_status, array('payment_received', 'completed'))) {
        watchdog('ePayco', "Confirming order !order_id but it is already completed. Its current status is !current_order_status.", $watchdog_variables, WATCHDOG_WARNING);
        uc_order_comment_save($response['x_extra4'], 0, t("Confirming order !order_id but it is already completed. Its current status is !current_order_status.", $watchdog_variables));
      }



      switch ($response['x_cod_transaction_state']) {

        case 1: // Payment Received

        $comment = t("Order Completed..") . ' ' . t("ePayco # !reference_pol", $watchdog_variables);
        uc_order_update_status($response['x_extra4'], 'completed');
        uc_order_comment_save($response['x_extra4'], 0, $comment, 'order', 'completed');
        uc_payment_enter($response['x_extra4'], 'epayco', $response['x_amount'], 0, NULL, $comment);
        uc_cart_empty($response['x_extra4']);
        echo "Order Completed.";
        watchdog('ePayco', "Processing order !order_id. ePayco # !reference_pol", $watchdog_variables);


        break;

        case 2: // Canceled
        $comment = t("Order Canceled.") . ' ' . t("ePayco # !reference_pol", $watchdog_variables);
        uc_order_update_status($response['x_extra4'], 'canceled');
        uc_order_comment_save($response['x_extra4'], 0, $comment, 'order', 'canceled');
        uc_payment_enter($response['x_extra4'], 'epayco', $response['x_amount'], 0, NULL, $comment);
        uc_epayco_restore_stock($order);
        echo "Order Canceled.";
        watchdog('ePayco', "Order !order_id canceled. ePayco # !reference_pol", $watchdog_variables);
        break;

        case 3: // Pending/Processing
        $comment = t("Processing Order.") . ' ' . t("ePayco # !reference_pol", $watchdog_variables);
        uc_order_update_status($response['x_extra4'], 'pending');
        uc_order_comment_save($response['x_extra4'], 0, $comment, 'order', 'pending');
        uc_cart_empty($response['x_extra4']);
        echo "Order Processing.";
        watchdog('ePayco', "Processing order !order_id. ePayco # !reference_pol", $watchdog_variables);
        break;

        case 4: // Rejected
        $comment = t("Order Rejected.") . ' ' . t("ePayco # !reference_pol", $watchdog_variables);
        uc_order_update_status($response['x_extra4'], 'canceled');
        uc_order_comment_save($response['x_extra4'], 0, $comment, 'order', 'canceled');
        uc_epayco_restore_stock($order);
        echo "Order Rejected.";
        watchdog('ePayco', "Order !order_id rejected. ePayco # !reference_pol", $watchdog_variables);
        break;

        case 6: // Reversada
        $comment = t("Order Rejected.") . ' ' . t("ePayco # !reference_pol", $watchdog_variables);
        uc_order_update_status($response['x_extra4'], 'canceled');
        uc_order_comment_save($response['x_extra4'], 0, $comment, 'order', 'canceled');
        uc_epayco_restore_stock($order);
        echo "Order Rejected.";
        watchdog('ePayco', "Order !order_id rejected. ePayco # !reference_pol", $watchdog_variables);
        break;

        case 7: // Pending/Held
        $comment = t("Processing Order.") . ' ' . t("ePayco # !reference_pol", $watchdog_variables);
        uc_order_update_status($response['x_extra4'], 'processing');
        uc_order_comment_save($response['x_extra4'], 0, $comment, 'order', 'processing');
        uc_cart_empty($response['x_extra4']);
        echo "Order Processing.";
        watchdog('ePayco', "Processing order !order_id. ePayco # !reference_pol", $watchdog_variables);
        break;

        case 8: // Hold/Pending
        $comment = t("In checkout Order.") . ' ' . t("ePayco # !reference_pol", $watchdog_variables);
        uc_order_update_status($response['x_extra4'], 'in checkout');
        uc_order_comment_save($response['x_extra4'], 0, $comment, 'order', 'in checkout');
        uc_cart_empty($response['x_extra4']);
        echo "Order Processing.";
        watchdog('ePayco', "Processing order !order_id. ePayco # !reference_pol", $watchdog_variables);
        break;

        case 9: // Expired
        $comment = t("Expired Order.") . ' ' . t("ePayco # !reference_pol", $watchdog_variables);
        uc_order_update_status($response['x_extra4'], 'abandoned');
        uc_order_comment_save($response['x_extra4'], 0, $comment, 'order', 'abandoned');
        uc_cart_empty($response['x_extra4']);
        uc_epayco_restore_stock($order);
        echo "Order Processing.";
        watchdog('ePayco', "Order !order_id rejected. ePayco # !reference_pol", $watchdog_variables);
        break;

        case 10: // Abandoned
        $comment = t("Abandoned Order.") . ' ' . t("ePayco # !reference_pol", $watchdog_variables);
        uc_order_update_status($response['x_extra4'], 'abandoned');
        uc_order_comment_save($response['x_extra4'], 0, $comment, 'order', 'abandoned');
        uc_cart_empty($response['x_extra4']);
        uc_epayco_restore_stock($order);
        echo "Order Processing.";
        watchdog('ePayco', "Order !order_id rejected. ePayco # !reference_pol", $watchdog_variables);
        break;

        case 11: // Canceled
        $comment = t("Order Canceled.") . ' ' . t("ePayco # !reference_pol", $watchdog_variables);
        uc_order_update_status($response['x_extra4'], 'canceled');
        uc_order_comment_save($response['x_extra4'], 0, $comment, 'order', 'canceled');
        uc_payment_enter($response['x_extra4'], 'epayco', $response['x_amount'], 0, NULL, $comment);
        uc_epayco_restore_stock($order);
        echo "Order Canceled.";
        watchdog('ePayco', "Order !order_id canceled. ePayco # !reference_pol", $watchdog_variables);
        break;

        case 12: // Anti fraud
        $comment = t("Order Canceled.") . ' ' . t("ePayco # !reference_pol", $watchdog_variables);
        uc_order_update_status($response['x_extra4'], 'canceled');
        uc_order_comment_save($response['x_extra4'], 0, $comment, 'order', 'canceled');
        uc_payment_enter($response['x_extra4'], 'epayco', $response['x_amount'], 0, NULL, $comment);
        uc_epayco_restore_stock($order);
        echo "Order Canceled.";
        watchdog('ePayco', "Order !order_id canceled. ePayco # !reference_pol", $watchdog_variables);
        break;

        default:
        $comment = t("Order Error.") . ' ' . t("ePayco # !reference_pol", $watchdog_variables);
        uc_order_comment_save($response['x_extra4'], 0, $comment, 'order', $order->order_status);
        echo "Error with order.";
        watchdog('ePayco', "Error with order !order_id. ePayco # !reference_pol", $watchdog_variables);

      }
    }
    else {
      watchdog('ePayco', "Confirming order !order_id but signature doesn't match.", $watchdog_variables, WATCHDOG_ERROR);
    }
  }
  else {
    watchdog('ePayco', "Confirming order !order_id but it doesn't exists.", $watchdog_variables, WATCHDOG_ERROR);
  }
}

function _uc_epayco_format_response($response) {
  $output = t('epayco response:');
  $output .= '<ul>';
  $output .= '<li>' . t('Sale Reference (!key): !value', array('!key' => 'reference_sale', '!value' => $response['reference_sale'])) . '</li>';
  $output .= '<li>' . t('Transaction status (!key): !value !info', array('!key' => 'state_pol', '!value' => $response['state_pol'], '!info' =>$response['x_response'])) . '</li>';
  $output .= '<li>' . t('Response code (!key): !value !info', array('!key' => 'response_code_pol', '!value' => $response['response_code_pol'], '!info' => $response['x_response'])) . '</li>';
  $output .= '</ul>';

  return $output;
}

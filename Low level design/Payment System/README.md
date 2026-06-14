Payment System - Design Overview
===============================

Summary
-------
This folder contains a small C++ design for a payment processing subsystem. The design demonstrates:
- A `PaymentRequest`/`PaymentResponse` model for requests and results.
- A `IPaymentProcessor` strategy interface with concrete processors for Card, NetBanking and UPI.
- A `IPaymentGateway` adapter interface that adapts external gateway behaviour to the processor layer.
- Concrete gateway adapters (e.g., `gpaypaymentGateway`, `mastercardPaymentGateway`) that use processors.
- A `GatewayFactory` to create gateway adapters based on `PaymentRequest` details.

Files
-----
- `paymentrequest.h` — request/response/status models and enums.
- `paymentprocessor.h` — `IPaymentProcessor` and concrete processors (`CardPaymentProcessor`, `NetBankingPaymentProcessor`, `UPIPaymentProcessor`).
- `paymentadapter.h` — `IPaymentGateway` adapter interface and concrete gateway adapters for UPI, Card and NetBanking providers.
- `gatewayfactory.h` — simple factory (`GatewayFactory::createPaymentGateway`) that chooses an adapter from a `PaymentRequest`.

Key Types & APIs
-----------------
- `PaymentRequest` (in `paymentrequest.h`)
	- Fields: `paymentId`, `amount`, `PaymentMethodType` (`CARD`, `NET_BANKING`, `UPI`, `WALLET`), and `paymentDetails` (map string->string).
	- Accessors: `getPaymentId()`, `getAmount()`.

- `PaymentResponse` and `PaymentStatus` (in `paymentrequest.h`)
	- `PaymentResponse(paymentId, status, message)` — contains `paymentstatustype` (`CANCELLED`, `SUCEESS`, `FAILED`, `REFUNDED`).

- `IPaymentProcessor` (in `paymentprocessor.h`)
	- Pure virtual: `void processPayment(PaymentRequest request)`.
	- Implementations: `CardPaymentProcessor`, `NetBankingPaymentProcessor`, `UPIPaymentProcessor`.

- `IPaymentGateway` (in `paymentadapter.h`)
	- Pure virtual methods:
		- `unique_ptr<PaymentResponse> pay(PaymentRequest request)`
		- `unique_ptr<PaymentStatus> getPaymentStatus(string paymentId)`
		- `unique_ptr<PaymentResponse> cancelPayment(string paymentId)`
		- `unique_ptr<PaymentResponse> refundPayment(string paymentId)`

- Gateway adapter classes (in `paymentadapter.h`)
	- UPI adapters: `gpaypaymentGateway`, `phonepepaymentGateway`, `credpaymentGateway` (use `UPIPaymentProcessor`).
	- Card adapters: `visaPaymentGateway`, `mastercardPaymentGateway`, `rupaycardpaymentGateway` (use `CardPaymentProcessor`).
	- NetBanking adapters: `hdfcbankPaymentGateway`, `SBIBankpaymentGateway` (use `NetBankingPaymentProcessor`).

- `GatewayFactory` (in `gatewayfactory.h`)
	- `static unique_ptr<IPaymentGateway> createPaymentGateway(PaymentRequest request)`
	- Chooses adapter based on `request.getPaymentMethod()` and `request.getPaymentDetails()` entries (e.g., `cardType`, `bankName`, `upiProvider`).

Design Notes
------------
- The design applies Strategy (`IPaymentProcessor`) for processing logic and Adapter (`IPaymentGateway`) to adapt gateway behaviour to processor interfaces.
- `GatewayFactory` centralizes adapter selection but currently uses hard-coded string keys and comparisons — this can be improved by a provider registry or configuration mapping.
- `PaymentRequest::paymentDetails` is a flexible key/value map used to pass provider-specific parameters; callers must provide expected keys (`cardType`, `bankName`, `upiProvider`).
- Error handling is minimal in these headers; production code should validate map lookups and handle missing keys or unknown values.

Usage Example
-------------
Minimal example flow (pseudocode):

```cpp
// Build a request for a Mastercard card payment
unordered_map<string,string> details = {{"cardType","mastercard"}};
PaymentRequest req("pay-123", 49.99, CARD, details);

auto gateway = GatewayFactory::createPaymentGateway(req);
auto response = gateway->pay(req);
auto status = gateway->getPaymentStatus(req.getPaymentId());
```

Extension Points
----------------
- Add new `IPaymentProcessor` subclasses for other payment flows (e.g., `WalletPaymentProcessor`).
- Add new `IPaymentGateway` adapters to integrate third-party SDKs; each adapter should internally use an appropriate `IPaymentProcessor`.
- Replace `GatewayFactory` with a configurable registry to avoid hard-coded string comparisons and to allow dynamic provider registration.

Limitations & TODO
-------------------
- Map lookups like `paymentDetails.at("cardType")` can throw — validate before use.
- `PaymentRequest` exposes `getPaymentRequest()` returning a copy; consider passing by const reference to avoid copies.
- No asynchronous or network-handling code: adapters call `processPayment` synchronously and return static responses. Real gateways will involve async HTTP/SDK calls and callbacks.

If you want, I can:
- Add a provider registry to `GatewayFactory`.
- Add simple unit-test harness demonstrating flows.
- Convert adapters to return error codes on missing details.


The payment flow would be:
Client
   |
   v
Payment Service
   |
   +--> Payment Validation
   |
   +--> Fraud Check
   |
   +--> Gateway Factory
              |
              +--> PhonePe Gateway
              +--> GPay Gateway
              +--> HDFC Gateway
              +--> Visa Gateway
   |
   +--> Persist Transaction
   |
   +--> Publish Event
   |
   +--> Return Response


   There are some important classes can be used and the design can be extended by adding the below class:

   FraudService
   RetryService
   NotificationService

   Refund Service
   Setlllement service
   reconcillation service

   State machine for payment cycles:

   ```
   CREATED
    |
   PENDING
    |
   SUCCESS
   FAILED
   REFUNDED

  ```


  
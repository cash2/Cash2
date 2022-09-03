// Copyright (c) 2011-2016 The Cryptonote developers
// Copyright (c) 2016-2019, The Karbo Developers
// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "PaymentServiceJsonRpcServer.h"

#include <functional>

#include "PaymentServiceJsonRpcMessages.h"
#include "WalletService.h"

#include "Serialization/JsonInputValueSerializer.h"
#include "Serialization/JsonOutputStreamSerializer.h"
#include "version.h"

namespace PaymentService {

PaymentServiceJsonRpcServer::PaymentServiceJsonRpcServer(System::Dispatcher& sys, System::Event& stopEvent, WalletService& service, Logging::ILogger& loggerGroup, std::string rpcConfigurationPassword) 
  : JsonRpcServer(sys, stopEvent, loggerGroup, rpcConfigurationPassword)
  , service(service)
  , logger(loggerGroup, "PaymentServiceJsonRpcServer")
{
                                                                                                                                                                                
  handlers.emplace("reset", jsonHandler<Reset::Request, Reset::Response>(std::bind(&PaymentServiceJsonRpcServer::handleReset, this, std::placeholders::_1, std::placeholders::_2)));
  handlers.emplace("createAddress", jsonHandler<CreateAddress::Request, CreateAddress::Response>(std::bind(&PaymentServiceJsonRpcServer::handleCreateAddress, this, std::placeholders::_1, std::placeholders::_2)));
  handlers.emplace("createAddressList", jsonHandler<CreateAddressList::Request, CreateAddressList::Response>(std::bind(&PaymentServiceJsonRpcServer::handleCreateAddressList, this, std::placeholders::_1, std::placeholders::_2)));
  handlers.emplace("deleteAddress", jsonHandler<DeleteAddress::Request, DeleteAddress::Response>(std::bind(&PaymentServiceJsonRpcServer::handleDeleteAddress, this, std::placeholders::_1, std::placeholders::_2)));

// uncomment code below to get things working again
/*

  handlers.emplace("getSpendPrivateKey", jsonHandler<GetSpendPrivateKey::Request, GetSpendPrivateKey::Response>(std::bind(&PaymentServiceJsonRpcServer::handleGetSpendPrivateKey, this, std::placeholders::_1, std::placeholders::_2)));
  handlers.emplace("getSpendPrivateKeys", jsonHandler<GetSpendPrivateKeys::Request, GetSpendPrivateKeys::Response>(std::bind(&PaymentServiceJsonRpcServer::handleGetSpendPrivateKeys, this, std::placeholders::_1, std::placeholders::_2)));

*/

  handlers.emplace("getBalance", jsonHandler<GetBalance::Request, GetBalance::Response>(std::bind(&PaymentServiceJsonRpcServer::handleGetBalance, this, std::placeholders::_1, std::placeholders::_2)));
  handlers.emplace("getBlockHashes", jsonHandler<GetBlockHashes::Request, GetBlockHashes::Response>(std::bind(&PaymentServiceJsonRpcServer::handleGetBlockHashes, this, std::placeholders::_1, std::placeholders::_2)));
  handlers.emplace("getTransactionHashes", jsonHandler<GetTransactionHashes::Request, GetTransactionHashes::Response>(std::bind(&PaymentServiceJsonRpcServer::handleGetTransactionHashes, this, std::placeholders::_1, std::placeholders::_2)));
  handlers.emplace("getTransactions", jsonHandler<GetTransactions::Request, GetTransactions::Response>(std::bind(&PaymentServiceJsonRpcServer::handleGetTransactions, this, std::placeholders::_1, std::placeholders::_2)));
  handlers.emplace("getUnconfirmedTransactionHashes", jsonHandler<GetUnconfirmedTransactionHashes::Request, GetUnconfirmedTransactionHashes::Response>(std::bind(&PaymentServiceJsonRpcServer::handleGetUnconfirmedTransactionHashes, this, std::placeholders::_1, std::placeholders::_2)));
  handlers.emplace("getTransaction", jsonHandler<GetTransaction::Request, GetTransaction::Response>(std::bind(&PaymentServiceJsonRpcServer::handleGetTransaction, this, std::placeholders::_1, std::placeholders::_2)));
  handlers.emplace("sendTransaction", jsonHandler<SendTransaction::Request, SendTransaction::Response>(std::bind(&PaymentServiceJsonRpcServer::handleSendTransaction, this, std::placeholders::_1, std::placeholders::_2)));
  handlers.emplace("createDelayedTransaction", jsonHandler<CreateDelayedTransaction::Request, CreateDelayedTransaction::Response>(std::bind(&PaymentServiceJsonRpcServer::handleCreateDelayedTransaction, this, std::placeholders::_1, std::placeholders::_2)));
  handlers.emplace("getDelayedTransactionHashes", jsonHandler<GetDelayedTransactionHashes::Request, GetDelayedTransactionHashes::Response>(std::bind(&PaymentServiceJsonRpcServer::handleGetDelayedTransactionHashes, this, std::placeholders::_1, std::placeholders::_2)));
  handlers.emplace("deleteDelayedTransaction", jsonHandler<DeleteDelayedTransaction::Request, DeleteDelayedTransaction::Response>(std::bind(&PaymentServiceJsonRpcServer::handleDeleteDelayedTransaction, this, std::placeholders::_1, std::placeholders::_2)));
  handlers.emplace("sendDelayedTransaction", jsonHandler<SendDelayedTransaction::Request, SendDelayedTransaction::Response>(std::bind(&PaymentServiceJsonRpcServer::handleSendDelayedTransaction, this, std::placeholders::_1, std::placeholders::_2)));
  handlers.emplace("getViewKey", jsonHandler<GetViewKey::Request, GetViewKey::Response>(std::bind(&PaymentServiceJsonRpcServer::handleGetViewKey, this, std::placeholders::_1, std::placeholders::_2)));
  handlers.emplace("getStatus", jsonHandler<GetStatus::Request, GetStatus::Response>(std::bind(&PaymentServiceJsonRpcServer::handleGetStatus, this, std::placeholders::_1, std::placeholders::_2)));
  handlers.emplace("getAddresses", jsonHandler<GetAddresses::Request, GetAddresses::Response>(std::bind(&PaymentServiceJsonRpcServer::handleGetAddresses, this, std::placeholders::_1, std::placeholders::_2)));

//TODO: uncomment below

/*

  handlers.emplace("validateAddress", jsonHandler<ValidateAddress::Request, ValidateAddress::Response>(std::bind(&PaymentServiceJsonRpcServer::handleValidateAddress, this, std::placeholders::_1, std::placeholders::_2)));

*/

  handlers.emplace("save", jsonHandler<Save::Request, Save::Response>(std::bind(&PaymentServiceJsonRpcServer::handleSave, this, std::placeholders::_1, std::placeholders::_2)));
}

void PaymentServiceJsonRpcServer::processJsonRpcRequest(const Common::JsonValue& req, Common::JsonValue& resp) {
  try {
    prepareJsonResponse(req, resp);

    // Check that the wallet RPC password of the request matches the RPC password set when the server was started
    std::string rpcConfigurationPassword = getRpcConfigurationPassword();

    if (rpcConfigurationPassword != "")
    {
      std::string clientRpcPassword = "";
    
      if (req.contains("rpcPassword") && req("rpcPassword").isString())
      {
        clientRpcPassword = req("rpcPassword").getString();
      }
      else if (!req.contains("rpcPassword"))
      {
        logger(Logging::WARNING) << "Missing rpcPassword key in JSON RPC request";
        makeMissingRpcPasswordKeyResponse(resp);
        return;
      }
      else
      {
        logger(Logging::WARNING) << "RPC password provided is invalid";
        makeInvalidRpcPasswordResponse(resp);
        return;
      }

      if (clientRpcPassword != rpcConfigurationPassword)
      {
        if (clientRpcPassword == "")
        {
          logger(Logging::WARNING) << "Your request does not include an RPC password";
        }
        else
        {
          logger(Logging::WARNING) << "Incorrect RPC password : " << clientRpcPassword;
        }

        makeIncorrectRpcPasswordResponse(resp);
        return;
      }

    }

    if (!req.contains("method")) {
      logger(Logging::WARNING) << "Field \"method\" is not found in json request: " << req;
      makeGenericErrorReponse(resp, "Invalid Request", -3600);
      return;
    }

    if (!req("method").isString()) {
      logger(Logging::WARNING) << "Field \"method\" is not a string type: " << req;
      makeGenericErrorReponse(resp, "Invalid Request", -3600);
      return;
    }

    std::string method = req("method").getString();

    auto it = handlers.find(method);
    if (it == handlers.end()) {
      logger(Logging::WARNING) << "Requested method not found: " << method;
      makeMethodNotFoundResponse(resp);
      return;
    }

    logger(Logging::DEBUGGING) << method << " request came";

    Common::JsonValue params(Common::JsonValue::OBJECT);
    if (req.contains("params")) {
      params = req("params");
    }

    it->second(params, resp);
  } catch (std::exception& e) {
    logger(Logging::WARNING) << "Error occurred while processing JsonRpc request: " << e.what();
    makeGenericErrorReponse(resp, e.what());
  }
}

                                                                                                                         
                                     
 

std::error_code PaymentServiceJsonRpcServer::handleReset(const Reset::Request& request, Reset::Response& response) {
  if (request.viewSecretKey.empty()) {
    return service.resetWallet();
  } else {
    return service.replaceWithNewWallet(request.viewSecretKey);
  }
}

std::error_code PaymentServiceJsonRpcServer::handleCreateAddress(const CreateAddress::Request& request, CreateAddress::Response& response) {
  if (request.spendSecretKey.empty() && request.spendPublicKey.empty()) {
    return service.createAddress(response.address);
  } else if (!request.spendSecretKey.empty()) {
    return service.createAddress(request.spendSecretKey, response.address);
  } else {
    return service.createTrackingAddress(request.spendPublicKey, response.address);
  }
}

std::error_code PaymentServiceJsonRpcServer::handleCreateAddressList(const CreateAddressList::Request& request, CreateAddressList::Response& response) {
  return service.createAddressList(request.spendPrivateKeys, response.addresses);
}

std::error_code PaymentServiceJsonRpcServer::handleDeleteAddress(const DeleteAddress::Request& request, DeleteAddress::Response& response) {
  return service.deleteAddress(request.address);
}

//TODO: uncomment below code to get things working again

/*

std::error_code PaymentServiceJsonRpcServer::handleGetSpendPrivateKey(const GetSpendPrivateKey::Request& request, GetSpendPrivateKey::Response& response) {
  return service.getSpendPrivateKey(request.address, response.spendPrivateKey);
}

std::error_code PaymentServiceJsonRpcServer::handleGetSpendPrivateKeys(const GetSpendPrivateKeys::Request& request, GetSpendPrivateKeys::Response& response) {
  return service.getSpendPrivateKeys(response.spendPrivateKeys);
}

*/

std::error_code PaymentServiceJsonRpcServer::handleGetBalance(const GetBalance::Request& request, GetBalance::Response& response) {
  if (!request.address.empty()) {
    return service.getBalance(request.address, response.availableBalance, response.lockedAmount);
  } else {
    return service.getBalance(response.availableBalance, response.lockedAmount);
  }
}

std::error_code PaymentServiceJsonRpcServer::handleGetBlockHashes(const GetBlockHashes::Request& request, GetBlockHashes::Response& response) {
  return service.getBlockHashes(request.firstBlockIndex, request.blockCount, response.blockHashes);
}

std::error_code PaymentServiceJsonRpcServer::handleGetTransactionHashes(const GetTransactionHashes::Request& request, GetTransactionHashes::Response& response) {
  if (!request.blockHash.empty()) {
    return service.getTransactionHashes(request.addresses, request.blockHash, request.blockCount, request.paymentId, response.items);
  } else {
    return service.getTransactionHashes(request.addresses, request.firstBlockIndex, request.blockCount, request.paymentId, response.items);
  }
}

std::error_code PaymentServiceJsonRpcServer::handleGetTransactions(const GetTransactions::Request& request, GetTransactions::Response& response) {
  if (!request.blockHash.empty()) {
    return service.getTransactions(request.addresses, request.blockHash, request.blockCount, request.paymentId, response.items);
  } else {
    return service.getTransactions(request.addresses, request.firstBlockIndex, request.blockCount, request.paymentId, response.items);
  }
}

std::error_code PaymentServiceJsonRpcServer::handleGetUnconfirmedTransactionHashes(const GetUnconfirmedTransactionHashes::Request& request, GetUnconfirmedTransactionHashes::Response& response) {
  return service.getUnconfirmedTransactionHashes(request.addresses, response.transactionHashes);
}

std::error_code PaymentServiceJsonRpcServer::handleGetTransaction(const GetTransaction::Request& request, GetTransaction::Response& response) {
  return service.getTransaction(request.transactionHash, response.transaction);
}

// Modified
std::error_code PaymentServiceJsonRpcServer::handleSendTransaction(const SendTransaction::Request& request, SendTransaction::Response& response) {
  return service.sendTransaction(request, response.transactionHash);
}

std::error_code PaymentServiceJsonRpcServer::handleCreateDelayedTransaction(const CreateDelayedTransaction::Request& request, CreateDelayedTransaction::Response& response) {
  return service.createDelayedTransaction(request, response.transactionHash);
}

std::error_code PaymentServiceJsonRpcServer::handleGetDelayedTransactionHashes(const GetDelayedTransactionHashes::Request& request, GetDelayedTransactionHashes::Response& response) {
  return service.getDelayedTransactionHashes(response.transactionHashes);
}

std::error_code PaymentServiceJsonRpcServer::handleDeleteDelayedTransaction(const DeleteDelayedTransaction::Request& request, DeleteDelayedTransaction::Response& response) {
  return service.deleteDelayedTransaction(request.transactionHash);
}

std::error_code PaymentServiceJsonRpcServer::handleSendDelayedTransaction(const SendDelayedTransaction::Request& request, SendDelayedTransaction::Response& response) {
  return service.sendDelayedTransaction(request.transactionHash);
}

std::error_code PaymentServiceJsonRpcServer::handleGetViewKey(const GetViewKey::Request& request, GetViewKey::Response& response) {
  return service.getViewKey(response.viewSecretKey);
}

// Modified
std::error_code PaymentServiceJsonRpcServer::handleGetStatus(const GetStatus::Request& request, GetStatus::Response& response) {
  response.cash2_software_version = PROJECT_VERSION_LONG;
  return service.getStatus(response.blockCount, response.knownBlockCount, response.lastBlockHash, response.peerCount);
}

//TODO: uncomment below

/*

std::error_code PaymentServiceJsonRpcServer::handleValidateAddress(const ValidateAddress::Request& request, ValidateAddress::Response& response) {
  return service.validateAddress(request.address, response.address_valid);
}

*/

std::error_code PaymentServiceJsonRpcServer::handleGetAddresses(const GetAddresses::Request& request, GetAddresses::Response& response) {
  return service.getAddresses(response.addresses);
}

// Modified
std::error_code PaymentServiceJsonRpcServer::handleSave(const Save::Request& request, Save::Response& response) {
  return service.saveWalletNoThrow();
}

} // end namespace PaymentService

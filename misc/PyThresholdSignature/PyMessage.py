from enum import Enum
import json


class Message:

  class Type(Enum):
    UNKNOWN=1
    GROUP_SETUP=2
    GROUP_SETUP_RESPONSE=3
    GROUP_SECRET_SETUP = 4
    GROUP_SECRET_RESPONSE=5
    SHARED_SECRET_SETUP=6
    SHARED_SECRET_SETUP_RES=7
    PRE_SIGNATURE_SETUP=8
    POOL_BUILDER_SETUP=9
    PRE_SIGNATURE_INTERMEDIARY=10
    POOL_BUILDER_INTERMEDIARY=11
    PRE_SIGNATURE_INTERMEDIARY_RESPONSE=12
    ENCRYPTED_COEFFICIENTS=13
    ENCRYPTED_COEFFICIENTS_RES=14
    ENCRYPTED_COEFFICIENTS_BROADCAST=15

  def __init__(self, type = Type.UNKNOWN):
    self.mType = type

  def getType(self):
    return self.mType

  def to_json(self):
    j = {}
    j["Type"] = Message.getStrByType(self.mType)
    return json.dumps(j)
  
  def from_json(self, typeStr):
    j = json.loads(typeStr)
    self.mType = Message.getTypeByStr(j["Type"])
  
  def __str__(self):
    return str(Message.getStrByType(self.mType))

  def __eq__(self, other):
    return (Message.getStrByType(self.mType) == Message.getStrByType(other.getType)) 

  @staticmethod
  def getTable():
    table = { 
      Message.Type.UNKNOWN: "Unknown",
      Message.Type.GROUP_SETUP:"GroupSetup",
      Message.Type.GROUP_SETUP_RESPONSE:"GroupSetupResponse",
      Message.Type.GROUP_SECRET_SETUP:"GroupSecretSetup",
      Message.Type.GROUP_SECRET_RESPONSE:"GroupSecretResponse",
      Message.Type.SHARED_SECRET_SETUP:"SharedSecretSetup",
      Message.Type.SHARED_SECRET_SETUP_RES:"SharedSecretSetupResponse",
      Message.Type.PRE_SIGNATURE_SETUP:"PreSignatureSetup",
      Message.Type.POOL_BUILDER_SETUP:"PoolBuilderSetup",
      Message.Type.PRE_SIGNATURE_INTERMEDIARY:"PreSignatureIntermediary",
      Message.Type.POOL_BUILDER_INTERMEDIARY:"PoolBuilderIntermediary",
      Message.Type.PRE_SIGNATURE_INTERMEDIARY_RESPONSE:"PreSignatureIntermediaryResponse",
      Message.Type.ENCRYPTED_COEFFICIENTS:"Encrypted Coefficients",
      Message.Type.ENCRYPTED_COEFFICIENTS_RES:"Encrypted Coefficients Response",
      Message.Type.ENCRYPTED_COEFFICIENTS_BROADCAST:"Encrypted Coefficients Broadcast"
    }
    return table

  @staticmethod
  def getStrByType(val):
    return Message.getTable()[val]

  @staticmethod
  def getTypeByStr(val):
    for _type, _str in Message.getTable().items():
        if (_str == val):
            return _type
    return Message.Type.UNKNOWN

  


if __name__ == '__main__':
    msg = Message(Message.Type.GROUP_SETUP_RESPONSE)
    _type = msg.to_json()
    msgGS = Message(Message.Type.GROUP_SETUP)
    msgGS.from_json(_type)
    print(msgGS)

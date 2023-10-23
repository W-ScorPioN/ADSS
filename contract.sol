pragma solidity >=0.4.8 <0.8.17;


contract DataSharing{

    function ecrecovery(bytes32 hash, bytes memory sig) public returns (address) {
        bytes32 r;
        bytes32 s;
        uint8 v;

        // address address_zero = 0;

        if (sig.length != 65) {
            return address(0);
        }

        assembly {
            r := mload(add(sig, 32))
            s := mload(add(sig, 64))
            v := and(mload(add(sig, 65)), 255)
        }

        // https://github.com/ethereum/go-ethereum/issues/2053
        if (v < 27) {
            v += 27;
        }

        if (v != 27 && v != 28) {
            return address(0);
        }

        return ecrecover(hash, v, r, s);
    }

    function ecverify(bytes32 hash, bytes memory sig, address signer) public returns (bool) {
        return signer == ecrecovery(hash, sig);
    }

    function toBytes1(uint256 x) public returns (bytes memory b) {
        b = new bytes(32);
        assembly { mstore(add(b, 32), x) }
    }

    // address sender = 0xFeA919D83E060e73C5A43Dc14Cfb61B7a94Cf7a4;
    // address receiver = 0xFeA919D83E060e73C5A43Dc14Cfb61B7a94Cf7a4;

    string publicKeyofSender;
    string publicKeyofReceiver;

    uint revenue = 0.0001 ether;

    struct Setting{
        string fileID;
        address sender;
        address receiver;
        uint totalAccessNum;
        uint currentAccessNum;
        string ct_msk;
    }

    Setting private setting;

    mapping(string => address) sendermap;
    mapping(string => address) receivermap;

    function register(uint8 identity, string memory key) public returns(bool){
        if(identity == 0){
            sendermap[key] = msg.sender;
            return true;
        }
        else if(identity == 1){
            receivermap[key] = msg.sender;
            return true;
        }
        else{
            return false;
        }
    }

    function uploadSetting(string memory fileID, address sender, address receiver, uint totalAccessNum, uint currentAccessNum, string memory ct_msk, uint hash, uint sig, address signer) public returns (bool){      
        
        setting.fileID = fileID;
        setting.sender = sender;
        setting.receiver = receiver;
        setting.totalAccessNum = totalAccessNum;
        setting.currentAccessNum = currentAccessNum;
        setting.ct_msk = ct_msk;
        if(ecverify(bytes32(hash), toBytes1(sig), signer) == true){
            return true;
        }
        else {
            return false;
        }
    }

    function request() public payable returns (uint){
        require(msg.value > revenue);
        require(setting.totalAccessNum > setting.currentAccessNum);
        setting.currentAccessNum = setting.currentAccessNum + 1;
        uint receipt = setting.currentAccessNum;
        return receipt;

    }


}